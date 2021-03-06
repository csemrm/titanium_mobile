/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
#ifdef USE_TI_MEDIAVIDEOPLAYER

#import "TiColor.h"
#import "TiFile.h"
#import "TiViewProxy.h"
#import <AVFoundation/AVFoundation.h>
#import <AVKit/AVKit.h>
#import <MediaPlayer/MediaPlayer.h>

typedef NS_ENUM(NSInteger, VideoTimeOption) {
  VideoTimeOptionNearestKeyFrame = 0,
  VideoTimeOptionExact,
};

typedef NS_ENUM(NSInteger, VideoRepeatMode) {
  VideoRepeatModeNone = 0,
  VideoRepeatModeOne,
};

typedef NS_ENUM(NSInteger, TiVideoPlayerPlaybackState) {
  TiVideoPlayerPlaybackStateUnknown = -1,
  TiVideoPlayerPlaybackStateStopped,
  TiVideoPlayerPlaybackStatePlaying,
  TiVideoPlayerPlaybackStatePaused,
  TiVideoPlayerPlaybackStateInterrupted,
  TiVideoPlayerPlaybackStateSeekingForward, // Not supported so far
  TiVideoPlayerPlaybackStateSeekingBackward, // Not supported so far
};

@interface TiMediaVideoPlayerProxy : TiViewProxy {
  @protected
  AVPlayerViewController *movie;
  AVPlayerItem *item;
  NSRecursiveLock *playerLock;
  BOOL playing;
  @private

  NSURL *url;
  TiColor *backgroundColor;
  NSMutableArray *views;
  TiFile *tempFile;
  KrollCallback *thumbnailCallback;
  NSUInteger callbackRequestCount;
  BOOL seekToZeroBeforePlay;

  NSMutableDictionary *loadProperties; // Used to set properties when the player is created
  BOOL sizeSet;

  // OK, this is ridiculous.  Sometimes (always?) views which are made invisible and removed are relayed.
  // This means their views are recreated.  For movie players, this means the movie is reloaded and plays.
  // We need some internal way whether or not to check if it's OK to create a view - this is it.
  BOOL reallyAttached;

  // Need to preserve status bar frame information when entering/exiting fullscreen to properly re-render
  // views when exiting it.
  BOOL statusBarWasHidden;

  // Have to track loading in the proxy in addition to the view, in case we load before the view should be rendered
  BOOL loaded;

  // Track the playback state for parity
  TiVideoPlayerPlaybackState _playbackState;
}

@property (nonatomic, readwrite, assign) id url;
@property (nonatomic, readwrite, assign) TiColor *backgroundColor;
@property (nonatomic, readonly) NSNumber *playing;
@property (nonatomic, copy) NSNumber *volume;
@property (nonatomic, readwrite, assign) NSNumber *pictureInPictureEnabled;

- (void)add:(id)proxy;
- (void)remove:(id)proxy;

// INTERNAL: Used by subclasses
- (void)configurePlayer;
- (void)restart;
- (void)stop:(id)args;
- (void)play:(id)args;
@end

#endif
