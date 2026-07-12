import { useEffect, useRef, useCallback } from "react";
import { invoke } from "@tauri-apps/api/core";
import { useSpotify } from "../state";

export function useSpotifyService() {
  const { state, setPlayback, setError, setLoading } =
    useSpotify();

  const progressIntervalRef = useRef<ReturnType<typeof setInterval> | null>(
    null,
  );
  const startTimeRef = useRef<number>(0);
  const initialProgressRef = useRef<number>(0);
  const prevTrackRef = useRef<string>("");
  const wasPlayingRef = useRef(false);

  // Sync interpolation anchor when track changes or playback resumes
  useEffect(() => {
    if (state.playback?.is_playing) {
      const resumed = !wasPlayingRef.current;
      const trackChanged =
        state.playback.track !== prevTrackRef.current;

      if (resumed || trackChanged) {
        startTimeRef.current = Date.now();
        initialProgressRef.current = state.playback.progress_ms;
      }
    }
    prevTrackRef.current = state.playback?.track ?? "";
    wasPlayingRef.current = state.playback?.is_playing ?? false;
  }, [state.playback?.track, state.playback?.is_playing]);

  // Smooth progress interpolation (1s ticks)
  useEffect(() => {
    if (state.playback?.is_playing) {
      progressIntervalRef.current = setInterval(() => {
        const elapsed = Date.now() - startTimeRef.current;
        const interpolated = initialProgressRef.current + elapsed;
        setPlayback({
          ...state.playback!,
          progress_ms: Math.min(
            interpolated,
            state.playback!.duration_ms,
          ),
        });
      }, 1000);
    }

    return () => {
      if (progressIntervalRef.current) {
        clearInterval(progressIntervalRef.current);
        progressIntervalRef.current = null;
      }
    };
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [state.playback?.is_playing, state.playback?.track]);

  const connect = useCallback(async () => {
    setLoading(true);
    setError(null);
    try {
      await invoke("spotify_connect");
    } catch (err) {
      setError(String(err));
    } finally {
      setLoading(false);
    }
  }, [setLoading, setError]);

  const disconnect = useCallback(async () => {
    setLoading(true);
    try {
      await invoke("spotify_disconnect");
    } catch (err) {
      setError(String(err));
    } finally {
      setLoading(false);
    }
  }, [setLoading, setError]);

  const play = useCallback(async () => {
    try {
      await invoke("spotify_play");
    } catch (err) {
      setError(String(err));
    }
  }, [setError]);

  const pause = useCallback(async () => {
    try {
      await invoke("spotify_pause");
    } catch (err) {
      setError(String(err));
    }
  }, [setError]);

  const next = useCallback(async () => {
    try {
      await invoke("spotify_next");
    } catch (err) {
      setError(String(err));
    }
  }, [setError]);

  const previous = useCallback(async () => {
    try {
      await invoke("spotify_previous");
    } catch (err) {
      setError(String(err));
    }
  }, [setError]);

  return {
    state,
    connect,
    disconnect,
    play,
    pause,
    next,
    previous,
  };
}
