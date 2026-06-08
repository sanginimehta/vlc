#include "libvlc_additions.h"
#include <vlc/vlc.h>
#include <assert.h>

static void test_player_initial_state(libvlc_instance_t *vlc)
{
    libvlc_media_player_t *mp = libvlc_media_player_new(vlc);
    assert(mp != NULL);
    assert(libvlc_media_player_is_playing(mp) == 0);
    libvlc_media_player_release(mp);
}

static void test_player_no_media(libvlc_instance_t *vlc)
{
    libvlc_media_player_t *mp = libvlc_media_player_new(vlc);
    assert(mp != NULL);
    libvlc_media_t *media = libvlc_media_player_get_media(mp);
    assert(media == NULL);
    libvlc_media_player_release(mp);
}

static void test_player_pause_state(libvlc_instance_t *vlc)
{
    libvlc_media_player_t *mp = libvlc_media_player_new(vlc);
    assert(mp != NULL);
    libvlc_media_player_set_pause(mp, 1);
    assert(libvlc_media_player_is_playing(mp) == 0);
    libvlc_media_player_release(mp);
}

int main(void)
{
    libvlc_instance_t *vlc = libvlc_new(0, NULL);
    assert(vlc != NULL);
    test_player_initial_state(vlc);
    test_player_no_media(vlc);
    test_player_pause_state(vlc);
    libvlc_free(vlc);
    return 0;
}
