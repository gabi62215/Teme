#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include "so_stdio.h"
#include "file.h"

SO_FILE *so_fopen(const char *pathname, const char *mode)
{
	SO_FILE *file;
	int fd;

	file = (SO_FILE *)malloc(sizeof(SO_FILE));
	if (!file)
		return NULL;

	if (strcmp(mode, "r") == 0)
		fd = open(pathname, O_RDONLY);
	else if (strcmp(mode, "r+") == 0)
		fd = open(pathname, O_RDWR);
	else if (strcmp(mode, "w") == 0)
		fd = open(pathname, O_WRONLY | O_TRUNC | O_CREAT, PERM);
	else if (strcmp(mode, "w+") == 0)
		fd = open(pathname, O_RDWR | O_TRUNC | O_CREAT, PERM);
	else if (strcmp(mode, "a") == 0)
		fd = open(pathname, O_WRONLY | O_APPEND | O_CREAT, PERM);
	else if (strcmp(mode, "a+") == 0)
		fd = open(pathname, O_RDWR | O_APPEND | O_CREAT, PERM);
	else
		return NULL;

	if (fd < 0)
		return NULL;

	file->fd = fd;
	file->buff_cursor_w = 0;
	file->buff_cursor_r = 0;
	file->buff_size_r = 0;
	file->end_of_file = 0;
	file->error = 0;
	file->cursor = 0;
	file->last_operation = NOP;
	memset(file->buffer_r, 0, BUFSIZE);
	memset(file->buffer_w, 0, BUFSIZE);

	return file;
}

int so_feof(SO_FILE *stream)
{
	if (!stream)
		return SO_EOF;
	return stream->end_of_file;
}

int so_ferror(SO_FILE *stream)
{
	if (!stream)
		return SO_EOF;
	return stream->error;
}

int so_fileno(SO_FILE *stream)
{
	if (!stream)
		return SO_EOF;
	return stream->fd;
}

long so_ftell(SO_FILE *stream)
{
	if (!stream)
		return SO_EOF;
	return stream->cursor;
}

int so_close(SO_FILE *stream)
{
	int ret;

	so_fflush(stream);
	ret = close(stream->fd);
	free(stream);

	return ret;
}

ssize_t xread(int fd, void *buf, size_t count)
{
	size_t bytes_read = 0;

	while (bytes_read < count) {
		ssize_t bytes_read_now = read(fd, buf + bytes_read,
									  count - bytes_read);

		if (bytes_read_now == 0) /* EOF */
			return bytes_read;

		if (bytes_read_now < 0) /* I/O error */
			return -1;

		bytes_read += bytes_read_now;
	}

	return bytes_read;
}

ssize_t xwrite(int fd, const void *buf, size_t count)
{
	size_t bytes_written = 0;

	while (bytes_written < count) {
		ssize_t bytes_written_now = write(fd, buf + bytes_written,
										  count - bytes_written);

		if (bytes_written_now <= 0) /* I/O error */
			return -1;

		bytes_written += bytes_written_now;
	}

	return bytes_written;
}

int so_fflush(SO_FILE *stream)
{
	if (!stream)
		return SO_EOF;

	int ret;

	ret = xwrite(stream->fd, stream->buffer_w, stream->buff_cursor_w);

	stream->buff_cursor_w = 0;
	stream->last_operation = WRITE;
	memset(stream->buffer_w, 0, BUFSIZE);

	return ret;
}

int so_fgetc(SO_FILE *stream)
{
	if (!stream)
		return SO_EOF;

	int ret;

	if (stream->buff_size_r == 0 || 
		stream->buff_cursor_r == stream->buff_size_r) {
		memset(stream->buffer_r, 0, BUFSIZE);
		ret = read(stream->fd, stream->buffer_r, BUFSIZE);
		if (ret < 0) {
			stream->error = 1;
			return SO_EOF;
		}

		stream->buff_size_r = ret;
		stream->buff_cursor_r = 0;
	}

	stream->cursor++;
	stream->buff_cursor_r++;
	stream->last_operation = READ;

	return stream->buffer_r[stream->buff_cursor_r - 1];
}

int so_fputc(int c, SO_FILE *stream)
{
	if (!stream)
		return SO_EOF;

	int ret;

	if (stream->buff_cursor_w == BUFSIZE) {
		ret = so_fflush(stream);
		if (ret != 0) 
			return SO_EOF;
	}

	stream->cursor++;
	stream->buffer_w[stream->buff_cursor_w] = c;
	stream->buff_cursor_w++;
	stream->last_operation = WRITE;

	return c;
}

size_t so_fread(void *ptr, size_t size, size_t nmemb, SO_FILE *stream)
{
	if (!stream)
		return 0;
	
	int bytes_read;
	int bytes_to_read = size * nmemb;
	int cursor = 0;

	while (bytes_to_read > 0) {
		if (stream->buff_size_r == 0 || 
			stream->buff_cursor_r == stream->buff_size_r) {
			memset(stream->buffer_r, 0, BUFSIZE);
			bytes_read = read(stream->fd, stream->buffer_r,BUFSIZE);
			if (bytes_read == 0) {
				stream->end_of_file = 1;
				return bytes_read;
			}

			stream->buff_size_r = bytes_read;
			stream->buff_cursor_r = 0;
			stream->cursor += bytes_read;
		}

		memcpy(ptr + cursor, stream->buffer_r + stream->buff_cursor_r, 
			stream->buff_size_r - stream->buff_cursor_r);
		bytes_to_read -= (stream->buff_size_r - stream->buff_cursor_r);
		stream->buff_cursor_r = stream->buff_size_r;
		cursor += (stream->buff_size_r - stream->buff_cursor_r);
	}

	stream->last_operation = READ;

	return cursor / size;
}

size_t so_fwrite(const void *ptr, size_t size, size_t nmemb, SO_FILE *stream)
{
	if (!stream)
		return 0;

	int bytes_written = 0;
	int bytes_to_write = size * nmemb;
	int cursor = 0;
	int copied_bytes = 0;

	so_fflush(stream);

	while (bytes_to_write > 0) {
		if (BUFSIZE == stream->buff_cursor_w) {
			bytes_written = so_fflush(stream);
			if(bytes_written < 0)
				return 0;
		}

		bytes_to_write -= copied_bytes;
		if (bytes_to_write > BUFSIZE)
			copied_bytes = BUFSIZE;
		else
			copied_bytes = bytes_to_write;
		memcpy(stream->buffer_w + stream->buff_cursor_w,ptr + cursor,
			copied_bytes);
		stream->buff_cursor_w += copied_bytes;
		cursor += copied_bytes;
	}

	stream->last_operation = READ;

	return cursor / size;
}

int so_fseek(SO_FILE *stream, long offset, int whence)
{
	if (!stream)
		return SO_EOF;
	int ret = -1;

	if (stream->last_operation == WRITE)
		so_fflush(stream);
	if (stream->last_operation == READ)
		memset(stream->buffer_r, 0, stream->buff_size_r);

	if (whence == SEEK_END || whence == SEEK_CUR || whence == SEEK_SET)
		ret = lseek(stream->fd, offset, whence);

	if (ret == -1) {
		stream->error = 1;
		return SO_EOF;
	}

	if (whence == SEEK_CUR)
		stream->cursor += offset;
	else if (whence == SEEK_SET)
		stream->cursor = offset;
	else if (whence == SEEK_END) {
		struct stat st;
		ret = fstat(stream->fd, &st);
		if (ret == -1) {
			stream->error = 1;
			return SO_EOF;
		}
		stream->cursor = st.st_size + offset;
	}

	return 0;
}

SO_FILE *so_popen(const char *command, const char *type)
{
	SO_FILE *file;
	int fds[2], ret;
	pid_t pid;
	int redirect;

	if (strcmp(type,"r") == 0)
		redirect = 0;
	else if (strcmp(type,"w") == 0)
		redirect = 1;
	else
		return NULL;

	ret = pipe(fds);
	if (ret != 0)
		return NULL;

	// r , w

	pid = fork();
	switch (pid) {
		case -1:
			close(fds[0]);
			close(fds[1]);
			return NULL;
		case 0:
			if (redirect == 0)  {
				close(fds[0]);
				dup2(fds[1], 1);
			} else {
				close(fds[1]);
				dup2(fds[0], 0);
			}

			/* execute command */
			execlp("sh", "sh", "-c", command, (char  *) NULL);
			break;
		default:
			file = (SO_FILE *)malloc(sizeof(SO_FILE));
			if (!file) {
				if (redirect == 0)
					close(fds[0]);
				else
					close(fds[1]);
				return NULL;
			}

			if (redirect == 0)
				file->fd = fds[0];
			else
				file->fd = fds[1];
			file->buff_cursor_w = 0;
			file->buff_cursor_r = 0;
			file->buff_size_r = 0;
			file->end_of_file = 0;
			file->error = 0;
			file->cursor = 0;
			file->last_operation = NOP;
			memset(file->buffer_r, 0 , BUFSIZE);
			memset(file->buffer_w, 0 , BUFSIZE);

			return file;
	}
	return NULL;
}
int so_pclose(SO_FILE *stream)
{
	if (!stream)
		return SO_EOF;

	int ret;

	ret = so_fflush(stream);

	close(stream->fd);
	ret = wait(NULL);
	free(stream);

	return ret;
}