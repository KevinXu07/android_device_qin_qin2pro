#include <errno.h>
#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main(void) {
    char name[128] = {0};
    int fd = open("/dev/input/event0", O_RDWR | O_CLOEXEC);
    if (fd < 0) { perror("open"); return 1; }
    if (ioctl(fd, EVIOCGNAME(sizeof(name)), name) < 0 || strcmp(name, "sc27xx:vibrator")) {
        fprintf(stderr, "Unexpected device: %s\n", name); close(fd); return 1;
    }
    struct ff_effect effect = {0};
    effect.type = FF_RUMBLE;
    effect.id = -1;
    effect.u.rumble.strong_magnitude = 0xffff;
    effect.u.rumble.weak_magnitude = 0xffff;
    effect.replay.length = 500;
    if (ioctl(fd, EVIOCSFF, &effect) < 0) { perror("EVIOCSFF"); close(fd); return 1; }
    struct input_event event = {0};
    event.type = EV_FF; event.code = effect.id; event.value = 1;
    if (write(fd, &event, sizeof(event)) != sizeof(event)) { perror("start"); close(fd); return 1; }
    printf("Started 500ms rumble on %s, effect=%d\n", name, effect.id);
    usleep(600000);
    event.value = 0;
    if (write(fd, &event, sizeof(event)) != sizeof(event)) { perror("stop"); close(fd); return 1; }
    if (ioctl(fd, EVIOCRMFF, effect.id) < 0) { perror("EVIOCRMFF"); close(fd); return 1; }
    close(fd);
    puts("Stopped and removed effect");
    return 0;
}
