/*
 * volume.c - libvlc audio volume and mute API smoke test
 *
 * Tests edge cases for the volume API not covered by existing tests:
 * boundary values, out-of-range inputs, and mute toggling.
 */

#include "test.h"

static void test_volume_default(const char **argv, int argc)
{
    test_log("Testing default volume is 100\n");

    libvlc_instance_t *vlc = libvlc_new(argc, argv);
    assert(vlc != NULL);

    libvlc_media_player_t *mp = libvlc_media_player_new(vlc);
    assert(mp != NULL);

    assert(libvlc_audio_get_volume(mp) == 100);

    libvlc_media_player_release(mp);
    libvlc_release(vlc);
}

static void test_volume_valid_range(const char **argv, int argc)
{
    test_log("Testing volume at boundary values (0, 100, 200)\n");

    libvlc_instance_t *vlc = libvlc_new(argc, argv);
    assert(vlc != NULL);

    libvlc_media_player_t *mp = libvlc_media_player_new(vlc);
    assert(mp != NULL);

    /* Minimum */
    assert(0 == libvlc_audio_set_volume(mp, 0));
    assert(libvlc_audio_get_volume(mp) == 0);

    /* Normal */
    assert(0 == libvlc_audio_set_volume(mp, 100));
    assert(libvlc_audio_get_volume(mp) == 100);

    /* Maximum (amplified) */
    assert(0 == libvlc_audio_set_volume(mp, 200));
    assert(libvlc_audio_get_volume(mp) == 200);

    libvlc_media_player_release(mp);
    libvlc_release(vlc);
}

static void test_volume_out_of_range(const char **argv, int argc)
{
    test_log("Testing out-of-range volume values are rejected\n");

    libvlc_instance_t *vlc = libvlc_new(argc, argv);
    assert(vlc != NULL);

    libvlc_media_player_t *mp = libvlc_media_player_new(vlc);
    assert(mp != NULL);

    int volume_before = libvlc_audio_get_volume(mp);

    /* Negative volume must fail */
    assert(-1 == libvlc_audio_set_volume(mp, -1));

    /* Volume above 200 must fail */
    assert(-1 == libvlc_audio_set_volume(mp, 201));

    /* Volume must be unchanged after a failed set */
    assert(libvlc_audio_get_volume(mp) == volume_before);

    libvlc_media_player_release(mp);
    libvlc_release(vlc);
}

static void test_mute_toggle(const char **argv, int argc)
{
    test_log("Testing mute set, unset, and toggle\n");

    libvlc_instance_t *vlc = libvlc_new(argc, argv);
    assert(vlc != NULL);

    libvlc_media_player_t *mp = libvlc_media_player_new(vlc);
    assert(mp != NULL);

    /* Start from a known state */
    libvlc_audio_set_mute(mp, 0);
    assert(libvlc_audio_get_mute(mp) == 0);

    /* Mute on */
    libvlc_audio_set_mute(mp, 1);
    assert(libvlc_audio_get_mute(mp) == 1);

    /* Mute off */
    libvlc_audio_set_mute(mp, 0);
    assert(libvlc_audio_get_mute(mp) == 0);

    /* Toggle on */
    libvlc_audio_toggle_mute(mp);
    assert(libvlc_audio_get_mute(mp) == 1);

    /* Toggle off */
    libvlc_audio_toggle_mute(mp);
    assert(libvlc_audio_get_mute(mp) == 0);

    libvlc_media_player_release(mp);
    libvlc_release(vlc);
}

int main(void)
{
    test_init();

    test_volume_default(test_defaults_args, test_defaults_nargs);
    test_volume_valid_range(test_defaults_args, test_defaults_nargs);
    test_volume_out_of_range(test_defaults_args, test_defaults_nargs);
    test_mute_toggle(test_defaults_args, test_defaults_nargs);

    return 0;
}
