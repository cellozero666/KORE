-------------------------------------
Translated Report (Full Report Below)
-------------------------------------
Process:             kore-companion [87598]
Path:                /Volumes/VOLUME/*/kore-companion.app/Contents/MacOS/kore-companion
Identifier:          com.kore.companion
Version:             0.1.0 (0.1.0)
Code Type:           ARM-64 (Native)
Role:                Foreground
Parent Process:      launchd [1]
Coalition:           com.kore.companion [38106]
User ID:             501

Date/Time:           2026-07-11 21:33:57.3252 -0300
Launch Time:         2026-07-11 21:33:56.9129 -0300
Hardware Model:      Mac16,10
OS Version:          macOS 26.5.2 (25F84)
Release Type:        User

Crash Reporter Key:  BDF41DE1-2765-3176-E799-80B9000A31CD
Incident Identifier: 2ECA8458-B5C9-4913-96AB-EDC9F06574EC

Time Awake Since Boot: 200000 seconds

System Integrity Protection: enabled

Triggered by Thread: 7, Dispatch Queue: com.apple.root.default-qos

Exception Type:    EXC_CRASH (SIGABRT)
Exception Codes:   0x0000000000000000, 0x0000000000000000

Termination Reason:  Namespace TCC, Code 0, 
This app has crashed because it attempted to access privacy-sensitive data without a usage description. The app's Info.plist must contain an NSBluetoothAlwaysUsageDescription key with a string value explaining to the user how the app uses this data.


Thread 0:: main Dispatch queue: com.apple.main-thread
0   libobjc.A.dylib               	       0x18d7462ac objc_autorelease + 332
1   AppKit                        	       0x192e28e6c _NXCreateWindow + 564
2   AppKit                        	       0x19217698c -[NSWindow _commonAwake] + 724
3   AppKit                        	       0x192099d94 -[NSWindow _commonInitFrame:styleMask:backing:defer:] + 1044
4   AppKit                        	       0x192099510 -[NSWindow _initContent:styleMask:backing:defer:contentView:] + 848
5   AppKit                        	       0x1920991b4 -[NSWindow initWithContentRect:styleMask:backing:defer:] + 48
6   TextInputUIMacHelper          	       0x2801244d4 -[TUINSWindow init] + 80
7   TextInputUIMacHelper          	       0x280124ff4 -[TUINSCursorUIController init] + 268
8   TextInputUIMacHelper          	       0x280124e74 __41+[TUINSCursorUIController sharedInstance]_block_invoke + 24
9   libdispatch.dylib             	       0x18d9fc4b0 _dispatch_client_callout + 16
10  libdispatch.dylib             	       0x18d9e5630 _dispatch_once_callout + 32
11  TextInputUIMacHelper          	       0x280124e58 +[TUINSCursorUIController sharedInstance] + 84
12  AppKit                        	       0x192f354ec -[NSTextInputContext(NSTextInputContext_PrivateWebKitSupport) setShowsCursorAccessories:] + 36
13  WebKit                        	       0x1b891dff8 WebKit::WebViewImpl::selectionDidChange() + 200
14  WebKit                        	       0x1b88de5bc WebKit::PageClientImpl::selectionDidChange() + 52
15  WebKit                        	       0x1b890c0c4 WebKit::WebPageProxy::didUpdateEditorState(WebKit::EditorState const&, WebKit::EditorState const&) + 320
16  WebKit                        	       0x1b8aabc50 WebKit::WebPageProxy::updateEditorState(WebKit::EditorState&&, WebKit::WebPageProxy::ShouldMergeVisualEditorState) + 692
17  WebKit                        	       0x1b87f7120 WebKit::RemoteLayerTreeDrawingAreaProxy::commitLayerTree(IPC::Connection&, WebKit::RemoteLayerTreeCommitBundle const&, WTF::HashMap<WTF::ObjectIdentifierGeneric<WebKit::ImageBufferSetIdentifierType, WTF::ObjectIdentifierMainThreadAccessTraits<unsigned long long>, unsigned long long>, std::__1::unique_ptr<WebKit::BufferSetBackendHandle, std::__1::default_delete<WebKit::BufferSetBackendHandle>>, WTF::DefaultHash<WTF::ObjectIdentifierGeneric<WebKit::ImageBufferSetIdentifierType, WTF::ObjectIdentifierMainThreadAccessTraits<unsigned long long>, unsigned long long>>, WTF::HashTraits<WTF::ObjectIdentifierGeneric<WebKit::ImageBufferSetIdentifierType, WTF::ObjectIdentifierMainThreadAccessTraits<unsigned long long>, unsigned long long>>, WTF::HashTraits<std::__1::unique_ptr<WebKit::BufferSetBackendHandle, std::__1::default_delete<WebKit::BufferSetBackendHandle>>>, WTF::HashTableTraits, (WTF::ShouldValidateKey)1, WTF::FastMalloc>&&) + 848
18  WebKit                        	       0x1b8445f6c WebKit::RemoteLayerTreeDrawingAreaProxy::didReceiveMessage(IPC::Connection&, IPC::Decoder&) + 2028
19  WebKit                        	       0x1b90862ec IPC::MessageReceiverMap::dispatchMessage(IPC::Connection&, IPC::Decoder&) + 348
20  WebKit                        	       0x1b8b2e510 WebKit::WebProcessProxy::dispatchMessage(IPC::Connection&, IPC::Decoder&) + 44
21  WebKit                        	       0x1b854cd14 WebKit::WebProcessProxy::didReceiveMessage(IPC::Connection&, IPC::Decoder&) + 1036
22  WebKit                        	       0x1b905cacc IPC::Connection::dispatchMessage(WTF::UniqueRef<IPC::Decoder>) + 324
23  WebKit                        	       0x1b905cfbc IPC::Connection::dispatchIncomingMessages() + 536
24  JavaScriptCore                	       0x1afc5fc20 WTF::RunLoop::performWork() + 460
25  JavaScriptCore                	       0x1afc611d0 WTF::RunLoop::performWork(void*) + 36
26  CoreFoundation                	       0x18dc5af30 __CFRUNLOOP_IS_CALLING_OUT_TO_A_SOURCE0_PERFORM_FUNCTION__ + 28
27  CoreFoundation                	       0x18dc5aec4 __CFRunLoopDoSource0 + 172
28  CoreFoundation                	       0x18dc5ac30 __CFRunLoopDoSources0 + 232
29  CoreFoundation                	       0x18dc59854 __CFRunLoopRun + 820
30  CoreFoundation                	       0x18dd2c1c4 _CFRunLoopRunSpecificWithOptions + 532
31  HIToolbox                     	       0x19aa3f560 RunCurrentEventLoopInMode + 320
32  HIToolbox                     	       0x19aa428bc ReceiveNextEventCommon + 488
33  HIToolbox                     	       0x19abcc14c _BlockUntilNextEventMatchingListInMode + 48
34  AppKit                        	       0x19273435c _DPSBlockUntilNextEventMatchingListInMode + 228
35  AppKit                        	       0x192088084 _DPSNextEvent + 576
36  AppKit                        	       0x192c1d8b0 -[NSApplication(NSEventRouting) _nextEventMatchingEventMask:untilDate:inMode:dequeue:] + 688
37  AppKit                        	       0x192c1d5bc -[NSApplication(NSEventRouting) nextEventMatchingMask:untilDate:inMode:dequeue:] + 72
38  AppKit                        	       0x19207b13c -[NSApplication run] + 368
39  kore-companion                	       0x102c3d2d0 tao::platform_impl::platform::event_loop::EventLoop$LT$T$GT$::run::h17b652263bbd06ee + 512
40  kore-companion                	       0x102c5b700 _$LT$tauri_runtime_wry..Wry$LT$T$GT$$u20$as$u20$tauri_runtime..Runtime$LT$T$GT$$GT$::run::hf3de48ef026a32db + 328
41  kore-companion                	       0x102b29660 kore_companion_lib::run::heeee3927d1ed827a + 9584
42  kore-companion                	       0x1029917b4 std::sys::backtrace::__rust_begin_short_backtrace::h57ca893ef5a3d214 + 12
43  kore-companion                	       0x10299179c std::rt::lang_start::_$u7b$$u7b$closure$u7d$$u7d$::hd712266dd296f15d + 16
44  kore-companion                	       0x102ffa5c8 _RNvNtCsaLOjE9VYtxK_3std2rt19lang_start_internal + 952
45  kore-companion                	       0x10299180c main + 52
46  dyld                          	       0x18d7dfe00 start + 6992

Thread 1:

Thread 2:

Thread 3:

Thread 4:: com.apple.NSEventThread
0   libsystem_kernel.dylib        	       0x18db59c34 mach_msg2_trap + 8
1   libsystem_kernel.dylib        	       0x18db6c574 mach_msg2_internal + 76
2   libsystem_kernel.dylib        	       0x18db629c0 mach_msg_overwrite + 480
3   libsystem_kernel.dylib        	       0x18db59fc0 mach_msg + 24
4   CoreFoundation                	       0x18dc5b0d8 __CFRunLoopServiceMachPort + 160
5   CoreFoundation                	       0x18dc599c4 __CFRunLoopRun + 1188
6   CoreFoundation                	       0x18dd2c1c4 _CFRunLoopRunSpecificWithOptions + 532
7   AppKit                        	       0x1921a9c7c _NSEventThread + 184
8   libsystem_pthread.dylib       	       0x18db9dc58 _pthread_start + 136
9   libsystem_pthread.dylib       	       0x18db98c1c thread_start + 8

Thread 5:: JavaScriptCore libpas scavenger
0   libsystem_kernel.dylib        	       0x18db5d50c __psynch_cvwait + 8
1   libsystem_pthread.dylib       	       0x18db9e128 _pthread_cond_wait + 980
2   JavaScriptCore                	       0x1b134b0bc scavenger_thread_main + 1416
3   libsystem_pthread.dylib       	       0x18db9dc58 _pthread_start + 136
4   libsystem_pthread.dylib       	       0x18db98c1c thread_start + 8

Thread 6:

Thread 7 Crashed::  Dispatch queue: com.apple.root.default-qos
0   libsystem_kernel.dylib        	       0x18db66b10 __abort_with_payload + 8
1   libsystem_kernel.dylib        	       0x18db8e0e8 abort_with_payload_wrapper_internal + 104
2   libsystem_kernel.dylib        	       0x18db8e11c abort_with_payload + 16
3   TCC                           	       0x194365ef0 __TCC_CRASHING_DUE_TO_PRIVACY_VIOLATION__ + 172
4   TCC                           	       0x19436683c __TCCAccessRequest_block_invoke.229 + 628
5   TCC                           	       0x19436382c __tccd_send_message_block_invoke + 632
6   libxpc.dylib                  	       0x18d87ac00 _xpc_connection_reply_callout + 120
7   libxpc.dylib                  	       0x18d87aaf8 _xpc_connection_call_reply_async + 96
8   libdispatch.dylib             	       0x18d9fc4e0 <deduplicated_symbol> + 16
9   libdispatch.dylib             	       0x18da0052c _dispatch_mach_msg_async_reply_invoke + 340
10  libdispatch.dylib             	       0x18d9f5b44 _dispatch_root_queue_drain_deferred_item + 216
11  libdispatch.dylib             	       0x18d9f5390 _dispatch_kevent_worker_thread + 536
12  libsystem_pthread.dylib       	       0x18db99ef8 _pthread_wqthread + 348
13  libsystem_pthread.dylib       	       0x18db98c10 start_wqthread + 8

Thread 8:: WebCore: Scrolling
0   libsystem_kernel.dylib        	       0x18db59c34 mach_msg2_trap + 8
1   libsystem_kernel.dylib        	       0x18db6c574 mach_msg2_internal + 76
2   libsystem_kernel.dylib        	       0x18db629c0 mach_msg_overwrite + 480
3   libsystem_kernel.dylib        	       0x18db59fc0 mach_msg + 24
4   CoreFoundation                	       0x18dc5b0d8 __CFRunLoopServiceMachPort + 160
5   CoreFoundation                	       0x18dc599c4 __CFRunLoopRun + 1188
6   CoreFoundation                	       0x18dd2c1c4 _CFRunLoopRunSpecificWithOptions + 532
7   CoreFoundation                	       0x18dccfaf4 CFRunLoopRun + 64
8   JavaScriptCore                	       0x1afc607d8 WTF::Detail::CallableWrapper<WTF::RunLoop::create(WTF::ASCIILiteral, WTF::ThreadType, WTF::Thread::QOS)::$_0, void>::call() + 244
9   JavaScriptCore                	       0x1afca8484 WTF::Thread::entryPoint(WTF::Thread::NewThreadContext*) + 300
10  JavaScriptCore                	       0x1afa77088 WTF::wtfThreadEntryPoint(void*) + 16
11  libsystem_pthread.dylib       	       0x18db9dc58 _pthread_start + 136
12  libsystem_pthread.dylib       	       0x18db98c1c thread_start + 8

Thread 9::  Dispatch queue: com.apple.root.user-interactive-qos
0   libsystem_kernel.dylib        	       0x18db59c34 mach_msg2_trap + 8
1   libsystem_kernel.dylib        	       0x18db6c574 mach_msg2_internal + 76
2   libsystem_kernel.dylib        	       0x18db629c0 mach_msg_overwrite + 480
3   libsystem_kernel.dylib        	       0x18db59fc0 mach_msg + 24
4   CoreFoundation                	       0x18dc5b0d8 __CFRunLoopServiceMachPort + 160
5   CoreFoundation                	       0x18dc599c4 __CFRunLoopRun + 1188
6   CoreFoundation                	       0x18dd2c1c4 _CFRunLoopRunSpecificWithOptions + 532
7   Foundation                    	       0x18f4a3b44 -[NSRunLoop(NSRunLoop) runMode:beforeDate:] + 212
8   AppKit                        	       0x19285a0cc -[NSAnimation _runBlocking] + 412
9   libdispatch.dylib             	       0x18d9e2a28 _dispatch_call_block_and_release + 32
10  libdispatch.dylib             	       0x18d9fc4b0 _dispatch_client_callout + 16
11  libdispatch.dylib             	       0x18da19d6c <deduplicated_symbol> + 28
12  libdispatch.dylib             	       0x18d9f4adc _dispatch_root_queue_drain + 708
13  libdispatch.dylib             	       0x18d9f5120 _dispatch_worker_thread2 + 184
14  libsystem_pthread.dylib       	       0x18db99e84 _pthread_wqthread + 232
15  libsystem_pthread.dylib       	       0x18db98c10 start_wqthread + 8

Thread 10:: CVDisplayLink
0   libsystem_kernel.dylib        	       0x18db5d50c __psynch_cvwait + 8
1   libsystem_pthread.dylib       	       0x18db9e154 _pthread_cond_wait + 1024
2   CoreVideo                     	       0x19855cb44 CVDisplayLink::waitUntil(unsigned long long) + 336
3   CoreVideo                     	       0x19855bc2c CVDisplayLink::runIOThread() + 452
4   libsystem_pthread.dylib       	       0x18db9dc58 _pthread_start + 136
5   libsystem_pthread.dylib       	       0x18db98c1c thread_start + 8

Thread 11:: CVDisplayLink
0   libsystem_kernel.dylib        	       0x18db5d50c __psynch_cvwait + 8
1   libsystem_pthread.dylib       	       0x18db9e154 _pthread_cond_wait + 1024
2   CoreVideo                     	       0x19855cb44 CVDisplayLink::waitUntil(unsigned long long) + 336
3   CoreVideo                     	       0x19855bc2c CVDisplayLink::runIOThread() + 452
4   libsystem_pthread.dylib       	       0x18db9dc58 _pthread_start + 136
5   libsystem_pthread.dylib       	       0x18db98c1c thread_start + 8

Thread 12:: tokio-rt-worker
0   libsystem_kernel.dylib        	       0x18db5d50c __psynch_cvwait + 8
1   libsystem_pthread.dylib       	       0x18db9e128 _pthread_cond_wait + 980
2   kore-companion                	       0x102ed1f10 parking_lot::condvar::Condvar::wait_until_internal::h7a8073d8c6fc70c3 + 552
3   kore-companion                	       0x102eafb70 tokio::runtime::scheduler::multi_thread::park::Inner::park_condvar::h7554bf8664fac1d7 + 208
4   kore-companion                	       0x102eb5838 tokio::runtime::scheduler::multi_thread::worker::Context::park_internal::h467e864812df67f8 + 384
5   kore-companion                	       0x102eb6a60 tokio::runtime::scheduler::multi_thread::worker::Context::run::h3f04c0f91a4668a3 + 3712
6   kore-companion                	       0x102ecc2c4 tokio::runtime::context::scoped::Scoped$LT$T$GT$::set::h3b819941c9378206 + 56
7   kore-companion                	       0x102eaf8cc tokio::runtime::context::runtime::enter_runtime::hed6f538e124ba00c + 492
8   kore-companion                	       0x102eb3f64 tokio::runtime::scheduler::multi_thread::worker::run::h750c64c6ac0235a6 + 176
9   kore-companion                	       0x102ebd6a0 _$LT$tokio..runtime..blocking..task..BlockingTask$LT$T$GT$$u20$as$u20$core..future..future..Future$GT$::poll::h28847489b1106f55 + 108
10  kore-companion                	       0x102ec2620 tokio::runtime::task::core::Core$LT$T$C$S$GT$::poll::h06297f738cd993bf + 164
11  kore-companion                	       0x102eae248 tokio::runtime::task::harness::Harness$LT$T$C$S$GT$::poll::h494a0f555e1b52e9 + 168
12  kore-companion                	       0x102ec0f80 tokio::runtime::blocking::pool::Inner::run::h69fc3caa6bb155fa + 260
13  kore-companion                	       0x102eb7a84 std::sys::backtrace::__rust_begin_short_backtrace::h3711ebb41b529b4e + 224
14  kore-companion                	       0x102eb829c core::ops::function::FnOnce::call_once$u7b$$u7b$vtable.shim$u7d$$u7d$::h5b590e309155afbc + 92
15  kore-companion                	       0x103001970 _RNvNvMs0_NtNtNtCsaLOjE9VYtxK_3std3sys6thread4unixNtB7_6Thread3new12thread_start + 408
16  libsystem_pthread.dylib       	       0x18db9dc58 _pthread_start + 136
17  libsystem_pthread.dylib       	       0x18db98c1c thread_start + 8

Thread 13:: tokio-rt-worker
0   libsystem_kernel.dylib        	       0x18db5d50c __psynch_cvwait + 8
1   libsystem_pthread.dylib       	       0x18db9e128 _pthread_cond_wait + 980
2   kore-companion                	       0x102ed1f10 parking_lot::condvar::Condvar::wait_until_internal::h7a8073d8c6fc70c3 + 552
3   kore-companion                	       0x102eafb70 tokio::runtime::scheduler::multi_thread::park::Inner::park_condvar::h7554bf8664fac1d7 + 208
4   kore-companion                	       0x102eb5838 tokio::runtime::scheduler::multi_thread::worker::Context::park_internal::h467e864812df67f8 + 384
5   kore-companion                	       0x102eb6a60 tokio::runtime::scheduler::multi_thread::worker::Context::run::h3f04c0f91a4668a3 + 3712
6   kore-companion                	       0x102ecc2c4 tokio::runtime::context::scoped::Scoped$LT$T$GT$::set::h3b819941c9378206 + 56
7   kore-companion                	       0x102eaf8cc tokio::runtime::context::runtime::enter_runtime::hed6f538e124ba00c + 492
8   kore-companion                	       0x102eb3f64 tokio::runtime::scheduler::multi_thread::worker::run::h750c64c6ac0235a6 + 176
9   kore-companion                	       0x102ebd6a0 _$LT$tokio..runtime..blocking..task..BlockingTask$LT$T$GT$$u20$as$u20$core..future..future..Future$GT$::poll::h28847489b1106f55 + 108
10  kore-companion                	       0x102ec2620 tokio::runtime::task::core::Core$LT$T$C$S$GT$::poll::h06297f738cd993bf + 164
11  kore-companion                	       0x102eae248 tokio::runtime::task::harness::Harness$LT$T$C$S$GT$::poll::h494a0f555e1b52e9 + 168
12  kore-companion                	       0x102ec0f80 tokio::runtime::blocking::pool::Inner::run::h69fc3caa6bb155fa + 260
13  kore-companion                	       0x102eb7a84 std::sys::backtrace::__rust_begin_short_backtrace::h3711ebb41b529b4e + 224
14  kore-companion                	       0x102eb829c core::ops::function::FnOnce::call_once$u7b$$u7b$vtable.shim$u7d$$u7d$::h5b590e309155afbc + 92
15  kore-companion                	       0x103001970 _RNvNvMs0_NtNtNtCsaLOjE9VYtxK_3std3sys6thread4unixNtB7_6Thread3new12thread_start + 408
16  libsystem_pthread.dylib       	       0x18db9dc58 _pthread_start + 136
17  libsystem_pthread.dylib       	       0x18db98c1c thread_start + 8

Thread 14:: tokio-rt-worker
0   libsystem_kernel.dylib        	       0x18db5ffc4 kevent + 8
1   kore-companion                	       0x102ed0fc0 mio::poll::Poll::poll::hb33eea066d8918e1 + 116
2   kore-companion                	       0x102ebc94c tokio::runtime::io::driver::Driver::turn::hcbb9c32ac53bf1a6 + 120
3   kore-companion                	       0x102eca910 tokio::runtime::time::Driver::park_internal::h257995291f8c752e + 740
4   kore-companion                	       0x102eb57a8 tokio::runtime::scheduler::multi_thread::worker::Context::park_internal::h467e864812df67f8 + 240
5   kore-companion                	       0x102eb6a60 tokio::runtime::scheduler::multi_thread::worker::Context::run::h3f04c0f91a4668a3 + 3712
6   kore-companion                	       0x102ecc2c4 tokio::runtime::context::scoped::Scoped$LT$T$GT$::set::h3b819941c9378206 + 56
7   kore-companion                	       0x102eaf8cc tokio::runtime::context::runtime::enter_runtime::hed6f538e124ba00c + 492
8   kore-companion                	       0x102eb3f64 tokio::runtime::scheduler::multi_thread::worker::run::h750c64c6ac0235a6 + 176
9   kore-companion                	       0x102ebd6a0 _$LT$tokio..runtime..blocking..task..BlockingTask$LT$T$GT$$u20$as$u20$core..future..future..Future$GT$::poll::h28847489b1106f55 + 108
10  kore-companion                	       0x102ec2620 tokio::runtime::task::core::Core$LT$T$C$S$GT$::poll::h06297f738cd993bf + 164
11  kore-companion                	       0x102eae248 tokio::runtime::task::harness::Harness$LT$T$C$S$GT$::poll::h494a0f555e1b52e9 + 168
12  kore-companion                	       0x102ec0f80 tokio::runtime::blocking::pool::Inner::run::h69fc3caa6bb155fa + 260
13  kore-companion                	       0x102eb7a84 std::sys::backtrace::__rust_begin_short_backtrace::h3711ebb41b529b4e + 224
14  kore-companion                	       0x102eb829c core::ops::function::FnOnce::call_once$u7b$$u7b$vtable.shim$u7d$$u7d$::h5b590e309155afbc + 92
15  kore-companion                	       0x103001970 _RNvNvMs0_NtNtNtCsaLOjE9VYtxK_3std3sys6thread4unixNtB7_6Thread3new12thread_start + 408
16  libsystem_pthread.dylib       	       0x18db9dc58 _pthread_start + 136
17  libsystem_pthread.dylib       	       0x18db98c1c thread_start + 8

Thread 15:: tokio-rt-worker
0   libsystem_kernel.dylib        	       0x18db5d50c __psynch_cvwait + 8
1   libsystem_pthread.dylib       	       0x18db9e128 _pthread_cond_wait + 980
2   kore-companion                	       0x102ed1f10 parking_lot::condvar::Condvar::wait_until_internal::h7a8073d8c6fc70c3 + 552
3   kore-companion                	       0x102eafb70 tokio::runtime::scheduler::multi_thread::park::Inner::park_condvar::h7554bf8664fac1d7 + 208
4   kore-companion                	       0x102eb5838 tokio::runtime::scheduler::multi_thread::worker::Context::park_internal::h467e864812df67f8 + 384
5   kore-companion                	       0x102eb6a60 tokio::runtime::scheduler::multi_thread::worker::Context::run::h3f04c0f91a4668a3 + 3712
6   kore-companion                	       0x102ecc2c4 tokio::runtime::context::scoped::Scoped$LT$T$GT$::set::h3b819941c9378206 + 56
7   kore-companion                	       0x102eaf8cc tokio::runtime::context::runtime::enter_runtime::hed6f538e124ba00c + 492
8   kore-companion                	       0x102eb3f64 tokio::runtime::scheduler::multi_thread::worker::run::h750c64c6ac0235a6 + 176
9   kore-companion                	       0x102ebd6a0 _$LT$tokio..runtime..blocking..task..BlockingTask$LT$T$GT$$u20$as$u20$core..future..future..Future$GT$::poll::h28847489b1106f55 + 108
10  kore-companion                	       0x102ec2620 tokio::runtime::task::core::Core$LT$T$C$S$GT$::poll::h06297f738cd993bf + 164
11  kore-companion                	       0x102eae248 tokio::runtime::task::harness::Harness$LT$T$C$S$GT$::poll::h494a0f555e1b52e9 + 168
12  kore-companion                	       0x102ec0f80 tokio::runtime::blocking::pool::Inner::run::h69fc3caa6bb155fa + 260
13  kore-companion                	       0x102eb7a84 std::sys::backtrace::__rust_begin_short_backtrace::h3711ebb41b529b4e + 224
14  kore-companion                	       0x102eb829c core::ops::function::FnOnce::call_once$u7b$$u7b$vtable.shim$u7d$$u7d$::h5b590e309155afbc + 92
15  kore-companion                	       0x103001970 _RNvNvMs0_NtNtNtCsaLOjE9VYtxK_3std3sys6thread4unixNtB7_6Thread3new12thread_start + 408
16  libsystem_pthread.dylib       	       0x18db9dc58 _pthread_start + 136
17  libsystem_pthread.dylib       	       0x18db98c1c thread_start + 8

Thread 16:: tokio-rt-worker
0   libsystem_kernel.dylib        	       0x18db5d50c __psynch_cvwait + 8
1   libsystem_pthread.dylib       	       0x18db9e128 _pthread_cond_wait + 980
2   kore-companion                	       0x102ed1f10 parking_lot::condvar::Condvar::wait_until_internal::h7a8073d8c6fc70c3 + 552
3   kore-companion                	       0x102eafb70 tokio::runtime::scheduler::multi_thread::park::Inner::park_condvar::h7554bf8664fac1d7 + 208
4   kore-companion                	       0x102eb5838 tokio::runtime::scheduler::multi_thread::worker::Context::park_internal::h467e864812df67f8 + 384
5   kore-companion                	       0x102eb6a60 tokio::runtime::scheduler::multi_thread::worker::Context::run::h3f04c0f91a4668a3 + 3712
6   kore-companion                	       0x102ecc2c4 tokio::runtime::context::scoped::Scoped$LT$T$GT$::set::h3b819941c9378206 + 56
7   kore-companion                	       0x102eaf8cc tokio::runtime::context::runtime::enter_runtime::hed6f538e124ba00c + 492
8   kore-companion                	       0x102eb3f64 tokio::runtime::scheduler::multi_thread::worker::run::h750c64c6ac0235a6 + 176
9   kore-companion                	       0x102ebd6a0 _$LT$tokio..runtime..blocking..task..BlockingTask$LT$T$GT$$u20$as$u20$core..future..future..Future$GT$::poll::h28847489b1106f55 + 108
10  kore-companion                	       0x102ec2620 tokio::runtime::task::core::Core$LT$T$C$S$GT$::poll::h06297f738cd993bf + 164
11  kore-companion                	       0x102eae248 tokio::runtime::task::harness::Harness$LT$T$C$S$GT$::poll::h494a0f555e1b52e9 + 168
12  kore-companion                	       0x102ec0f80 tokio::runtime::blocking::pool::Inner::run::h69fc3caa6bb155fa + 260
13  kore-companion                	       0x102eb7a84 std::sys::backtrace::__rust_begin_short_backtrace::h3711ebb41b529b4e + 224
14  kore-companion                	       0x102eb829c core::ops::function::FnOnce::call_once$u7b$$u7b$vtable.shim$u7d$$u7d$::h5b590e309155afbc + 92
15  kore-companion                	       0x103001970 _RNvNvMs0_NtNtNtCsaLOjE9VYtxK_3std3sys6thread4unixNtB7_6Thread3new12thread_start + 408
16  libsystem_pthread.dylib       	       0x18db9dc58 _pthread_start + 136
17  libsystem_pthread.dylib       	       0x18db98c1c thread_start + 8

Thread 17:: tokio-rt-worker
0   libsystem_kernel.dylib        	       0x18db5d50c __psynch_cvwait + 8
1   libsystem_pthread.dylib       	       0x18db9e128 _pthread_cond_wait + 980
2   kore-companion                	       0x102ed1f10 parking_lot::condvar::Condvar::wait_until_internal::h7a8073d8c6fc70c3 + 552
3   kore-companion                	       0x102eafb70 tokio::runtime::scheduler::multi_thread::park::Inner::park_condvar::h7554bf8664fac1d7 + 208
4   kore-companion                	       0x102eb5838 tokio::runtime::scheduler::multi_thread::worker::Context::park_internal::h467e864812df67f8 + 384
5   kore-companion                	       0x102eb6a60 tokio::runtime::scheduler::multi_thread::worker::Context::run::h3f04c0f91a4668a3 + 3712
6   kore-companion                	       0x102ecc2c4 tokio::runtime::context::scoped::Scoped$LT$T$GT$::set::h3b819941c9378206 + 56
7   kore-companion                	       0x102eaf8cc tokio::runtime::context::runtime::enter_runtime::hed6f538e124ba00c + 492
8   kore-companion                	       0x102eb3f64 tokio::runtime::scheduler::multi_thread::worker::run::h750c64c6ac0235a6 + 176
9   kore-companion                	       0x102ebd6a0 _$LT$tokio..runtime..blocking..task..BlockingTask$LT$T$GT$$u20$as$u20$core..future..future..Future$GT$::poll::h28847489b1106f55 + 108
10  kore-companion                	       0x102ec2620 tokio::runtime::task::core::Core$LT$T$C$S$GT$::poll::h06297f738cd993bf + 164
11  kore-companion                	       0x102eae248 tokio::runtime::task::harness::Harness$LT$T$C$S$GT$::poll::h494a0f555e1b52e9 + 168
12  kore-companion                	       0x102ec0f80 tokio::runtime::blocking::pool::Inner::run::h69fc3caa6bb155fa + 260
13  kore-companion                	       0x102eb7a84 std::sys::backtrace::__rust_begin_short_backtrace::h3711ebb41b529b4e + 224
14  kore-companion                	       0x102eb829c core::ops::function::FnOnce::call_once$u7b$$u7b$vtable.shim$u7d$$u7d$::h5b590e309155afbc + 92
15  kore-companion                	       0x103001970 _RNvNvMs0_NtNtNtCsaLOjE9VYtxK_3std3sys6thread4unixNtB7_6Thread3new12thread_start + 408
16  libsystem_pthread.dylib       	       0x18db9dc58 _pthread_start + 136
17  libsystem_pthread.dylib       	       0x18db98c1c thread_start + 8

Thread 18:: tokio-rt-worker
0   libsystem_kernel.dylib        	       0x18db5d50c __psynch_cvwait + 8
1   libsystem_pthread.dylib       	       0x18db9e128 _pthread_cond_wait + 980
2   kore-companion                	       0x102ed1f10 parking_lot::condvar::Condvar::wait_until_internal::h7a8073d8c6fc70c3 + 552
3   kore-companion                	       0x102eafb70 tokio::runtime::scheduler::multi_thread::park::Inner::park_condvar::h7554bf8664fac1d7 + 208
4   kore-companion                	       0x102eb5838 tokio::runtime::scheduler::multi_thread::worker::Context::park_internal::h467e864812df67f8 + 384
5   kore-companion                	       0x102eb6a60 tokio::runtime::scheduler::multi_thread::worker::Context::run::h3f04c0f91a4668a3 + 3712
6   kore-companion                	       0x102ecc2c4 tokio::runtime::context::scoped::Scoped$LT$T$GT$::set::h3b819941c9378206 + 56
7   kore-companion                	       0x102eaf8cc tokio::runtime::context::runtime::enter_runtime::hed6f538e124ba00c + 492
8   kore-companion                	       0x102eb3f64 tokio::runtime::scheduler::multi_thread::worker::run::h750c64c6ac0235a6 + 176
9   kore-companion                	       0x102ebd6a0 _$LT$tokio..runtime..blocking..task..BlockingTask$LT$T$GT$$u20$as$u20$core..future..future..Future$GT$::poll::h28847489b1106f55 + 108
10  kore-companion                	       0x102ec2620 tokio::runtime::task::core::Core$LT$T$C$S$GT$::poll::h06297f738cd993bf + 164
11  kore-companion                	       0x102eae248 tokio::runtime::task::harness::Harness$LT$T$C$S$GT$::poll::h494a0f555e1b52e9 + 168
12  kore-companion                	       0x102ec0f80 tokio::runtime::blocking::pool::Inner::run::h69fc3caa6bb155fa + 260
13  kore-companion                	       0x102eb7a84 std::sys::backtrace::__rust_begin_short_backtrace::h3711ebb41b529b4e + 224
14  kore-companion                	       0x102eb829c core::ops::function::FnOnce::call_once$u7b$$u7b$vtable.shim$u7d$$u7d$::h5b590e309155afbc + 92
15  kore-companion                	       0x103001970 _RNvNvMs0_NtNtNtCsaLOjE9VYtxK_3std3sys6thread4unixNtB7_6Thread3new12thread_start + 408
16  libsystem_pthread.dylib       	       0x18db9dc58 _pthread_start + 136
17  libsystem_pthread.dylib       	       0x18db98c1c thread_start + 8

Thread 19:: tokio-rt-worker
0   libsystem_kernel.dylib        	       0x18db5d50c __psynch_cvwait + 8
1   libsystem_pthread.dylib       	       0x18db9e128 _pthread_cond_wait + 980
2   kore-companion                	       0x102ed1f10 parking_lot::condvar::Condvar::wait_until_internal::h7a8073d8c6fc70c3 + 552
3   kore-companion                	       0x102eafb70 tokio::runtime::scheduler::multi_thread::park::Inner::park_condvar::h7554bf8664fac1d7 + 208
4   kore-companion                	       0x102eb5838 tokio::runtime::scheduler::multi_thread::worker::Context::park_internal::h467e864812df67f8 + 384
5   kore-companion                	       0x102eb6a60 tokio::runtime::scheduler::multi_thread::worker::Context::run::h3f04c0f91a4668a3 + 3712
6   kore-companion                	       0x102ecc2c4 tokio::runtime::context::scoped::Scoped$LT$T$GT$::set::h3b819941c9378206 + 56
7   kore-companion                	       0x102eaf8cc tokio::runtime::context::runtime::enter_runtime::hed6f538e124ba00c + 492
8   kore-companion                	       0x102eb3f64 tokio::runtime::scheduler::multi_thread::worker::run::h750c64c6ac0235a6 + 176
9   kore-companion                	       0x102ebd6a0 _$LT$tokio..runtime..blocking..task..BlockingTask$LT$T$GT$$u20$as$u20$core..future..future..Future$GT$::poll::h28847489b1106f55 + 108
10  kore-companion                	       0x102ec2620 tokio::runtime::task::core::Core$LT$T$C$S$GT$::poll::h06297f738cd993bf + 164
11  kore-companion                	       0x102eae248 tokio::runtime::task::harness::Harness$LT$T$C$S$GT$::poll::h494a0f555e1b52e9 + 168
12  kore-companion                	       0x102ec0f80 tokio::runtime::blocking::pool::Inner::run::h69fc3caa6bb155fa + 260
13  kore-companion                	       0x102eb7a84 std::sys::backtrace::__rust_begin_short_backtrace::h3711ebb41b529b4e + 224
14  kore-companion                	       0x102eb829c core::ops::function::FnOnce::call_once$u7b$$u7b$vtable.shim$u7d$$u7d$::h5b590e309155afbc + 92
15  kore-companion                	       0x103001970 _RNvNvMs0_NtNtNtCsaLOjE9VYtxK_3std3sys6thread4unixNtB7_6Thread3new12thread_start + 408
16  libsystem_pthread.dylib       	       0x18db9dc58 _pthread_start + 136
17  libsystem_pthread.dylib       	       0x18db98c1c thread_start + 8

Thread 20:: tokio-rt-worker
0   libsystem_kernel.dylib        	       0x18db5d50c __psynch_cvwait + 8
1   libsystem_pthread.dylib       	       0x18db9e128 _pthread_cond_wait + 980
2   kore-companion                	       0x102ed1f10 parking_lot::condvar::Condvar::wait_until_internal::h7a8073d8c6fc70c3 + 552
3   kore-companion                	       0x102eafb70 tokio::runtime::scheduler::multi_thread::park::Inner::park_condvar::h7554bf8664fac1d7 + 208
4   kore-companion                	       0x102eb5838 tokio::runtime::scheduler::multi_thread::worker::Context::park_internal::h467e864812df67f8 + 384
5   kore-companion                	       0x102eb6a60 tokio::runtime::scheduler::multi_thread::worker::Context::run::h3f04c0f91a4668a3 + 3712
6   kore-companion                	       0x102ecc2c4 tokio::runtime::context::scoped::Scoped$LT$T$GT$::set::h3b819941c9378206 + 56
7   kore-companion                	       0x102eaf8cc tokio::runtime::context::runtime::enter_runtime::hed6f538e124ba00c + 492
8   kore-companion                	       0x102eb3f64 tokio::runtime::scheduler::multi_thread::worker::run::h750c64c6ac0235a6 + 176
9   kore-companion                	       0x102ebd6a0 _$LT$tokio..runtime..blocking..task..BlockingTask$LT$T$GT$$u20$as$u20$core..future..future..Future$GT$::poll::h28847489b1106f55 + 108
10  kore-companion                	       0x102ec2620 tokio::runtime::task::core::Core$LT$T$C$S$GT$::poll::h06297f738cd993bf + 164
11  kore-companion                	       0x102eae248 tokio::runtime::task::harness::Harness$LT$T$C$S$GT$::poll::h494a0f555e1b52e9 + 168
12  kore-companion                	       0x102ec0f80 tokio::runtime::blocking::pool::Inner::run::h69fc3caa6bb155fa + 260
13  kore-companion                	       0x102eb7a84 std::sys::backtrace::__rust_begin_short_backtrace::h3711ebb41b529b4e + 224
14  kore-companion                	       0x102eb829c core::ops::function::FnOnce::call_once$u7b$$u7b$vtable.shim$u7d$$u7d$::h5b590e309155afbc + 92
15  kore-companion                	       0x103001970 _RNvNvMs0_NtNtNtCsaLOjE9VYtxK_3std3sys6thread4unixNtB7_6Thread3new12thread_start + 408
16  libsystem_pthread.dylib       	       0x18db9dc58 _pthread_start + 136
17  libsystem_pthread.dylib       	       0x18db98c1c thread_start + 8

Thread 21:: tokio-rt-worker
0   libsystem_kernel.dylib        	       0x18db5d50c __psynch_cvwait + 8
1   libsystem_pthread.dylib       	       0x18db9e128 _pthread_cond_wait + 980
2   kore-companion                	       0x102ed1f10 parking_lot::condvar::Condvar::wait_until_internal::h7a8073d8c6fc70c3 + 552
3   kore-companion                	       0x102eafb70 tokio::runtime::scheduler::multi_thread::park::Inner::park_condvar::h7554bf8664fac1d7 + 208
4   kore-companion                	       0x102eb5838 tokio::runtime::scheduler::multi_thread::worker::Context::park_internal::h467e864812df67f8 + 384
5   kore-companion                	       0x102eb6a60 tokio::runtime::scheduler::multi_thread::worker::Context::run::h3f04c0f91a4668a3 + 3712
6   kore-companion                	       0x102ecc2c4 tokio::runtime::context::scoped::Scoped$LT$T$GT$::set::h3b819941c9378206 + 56
7   kore-companion                	       0x102eaf8cc tokio::runtime::context::runtime::enter_runtime::hed6f538e124ba00c + 492
8   kore-companion                	       0x102eb3f64 tokio::runtime::scheduler::multi_thread::worker::run::h750c64c6ac0235a6 + 176
9   kore-companion                	       0x102ebd6a0 _$LT$tokio..runtime..blocking..task..BlockingTask$LT$T$GT$$u20$as$u20$core..future..future..Future$GT$::poll::h28847489b1106f55 + 108
10  kore-companion                	       0x102ec2620 tokio::runtime::task::core::Core$LT$T$C$S$GT$::poll::h06297f738cd993bf + 164
11  kore-companion                	       0x102eae248 tokio::runtime::task::harness::Harness$LT$T$C$S$GT$::poll::h494a0f555e1b52e9 + 168
12  kore-companion                	       0x102ec0f80 tokio::runtime::blocking::pool::Inner::run::h69fc3caa6bb155fa + 260
13  kore-companion                	       0x102eb7a84 std::sys::backtrace::__rust_begin_short_backtrace::h3711ebb41b529b4e + 224
14  kore-companion                	       0x102eb829c core::ops::function::FnOnce::call_once$u7b$$u7b$vtable.shim$u7d$$u7d$::h5b590e309155afbc + 92
15  kore-companion                	       0x103001970 _RNvNvMs0_NtNtNtCsaLOjE9VYtxK_3std3sys6thread4unixNtB7_6Thread3new12thread_start + 408
16  libsystem_pthread.dylib       	       0x18db9dc58 _pthread_start + 136
17  libsystem_pthread.dylib       	       0x18db98c1c thread_start + 8

Thread 22:

Thread 23:

Thread 24:

Thread 25:: Log work queue
0   libsystem_kernel.dylib        	       0x18db59bb0 semaphore_wait_trap + 8
1   WebKit                        	       0x1b908c98c IPC::StreamConnectionWorkQueue::startProcessingThread()::$_0::operator()() + 48
2   JavaScriptCore                	       0x1afca8484 WTF::Thread::entryPoint(WTF::Thread::NewThreadContext*) + 300
3   JavaScriptCore                	       0x1afa77088 WTF::wtfThreadEntryPoint(void*) + 16
4   libsystem_pthread.dylib       	       0x18db9dc58 _pthread_start + 136
5   libsystem_pthread.dylib       	       0x18db98c1c thread_start + 8

Thread 26:
0   libsystem_kernel.dylib        	       0x18db5d50c __psynch_cvwait + 8
1   libsystem_pthread.dylib       	       0x18db9e128 _pthread_cond_wait + 980
2   kore-companion                	       0x102ed1f10 parking_lot::condvar::Condvar::wait_until_internal::h7a8073d8c6fc70c3 + 552
3   kore-companion                	       0x102ec6c98 tokio::runtime::park::Inner::park::h774be44801d85c39 + 96
4   kore-companion                	       0x102ecd424 tokio::runtime::scheduler::current_thread::Context::park_internal::ha3e118a43adf1c40 + 160
5   kore-companion                	       0x102ecd870 tokio::runtime::scheduler::current_thread::Context::park::h952215f60a571b6b + 572
6   kore-companion                	       0x102dbb0f8 tokio::runtime::context::scoped::Scoped$LT$T$GT$::set::h9812401c9743de57 + 316
7   kore-companion                	       0x102dc18c4 tokio::runtime::scheduler::current_thread::CoreGuard::block_on::ha938b86b18d880e1 + 236
8   kore-companion                	       0x102dbb4b4 tokio::runtime::context::runtime::enter_runtime::h3200400801bccd7f + 844
9   kore-companion                	       0x102db7d0c tokio::runtime::runtime::Runtime::block_on::haf37f80d4a9b88a7 + 176
10  kore-companion                	       0x102dd9e64 std::sys::backtrace::__rust_begin_short_backtrace::h10846183136523a1 + 144
11  kore-companion                	       0x102da82ec core::ops::function::FnOnce::call_once$u7b$$u7b$vtable.shim$u7d$$u7d$::had4ee56b2cd17f44 + 104
12  kore-companion                	       0x103001970 _RNvNvMs0_NtNtNtCsaLOjE9VYtxK_3std3sys6thread4unixNtB7_6Thread3new12thread_start + 408
13  libsystem_pthread.dylib       	       0x18db9dc58 _pthread_start + 136
14  libsystem_pthread.dylib       	       0x18db98c1c thread_start + 8


Thread 7 crashed with ARM Thread State (64-bit):
    x0: 0x000000000000000b   x1: 0x0000000000000000   x2: 0x0000000a76675230   x3: 0x0000000000000022
    x4: 0x0000000a76675264   x5: 0x0000000000000000   x6: 0x00fb000004220122   x7: 0x000000016d83f0e0
    x8: 0x0000000000000020   x9: 0xb1f7c5155d1b0030  x10: 0x0100000100000000  x11: 0x000000000046ac31
   x12: 0x06cd613a02051004  x13: 0x0200000110000ca0  x14: 0x0000020000001000  x15: 0x0200000010000b70
   x16: 0x0000000000000209  x17: 0x00000001fb3e3188  x18: 0x0000000000000000  x19: 0x0000000000000000
   x20: 0x0000000a76675264  x21: 0x0000000000000022  x22: 0x0000000a76675230  x23: 0x0000000000000000
   x24: 0x000000000000000b  x25: 0x0000000a76be7000  x26: 0x0000000000000000  x27: 0x0000000000000000
   x28: 0x0000000000000000   fp: 0x000000016d83e630   lr: 0x000000018db8e0e8
    sp: 0x000000016d83e5f0   pc: 0x000000018db66b10 cpsr: 0x40000000
   far: 0x0000000000000000  esr: 0x56000080 (Syscall)

Binary Images:
       0x102990000 -        0x103353fff com.kore.companion (0.1.0) <0f7e9ca5-40a1-3f24-85f9-b7965689fb82> /Volumes/VOLUME/*/kore-companion.app/Contents/MacOS/kore-companion
       0x103984000 -        0x10398ffff libobjc-trampolines.dylib (*) <ca58aa96-b997-3a6d-9132-19d49be4b3e9> /usr/lib/libobjc-trampolines.dylib
       0x117d84000 -        0x1185fbfff com.apple.AGXMetalG16G-B0 (351.2) <f763c26f-f4b8-3a78-858d-23e30c8e2485> /System/Library/Extensions/AGXMetalG16G_B0.bundle/Contents/MacOS/AGXMetalG16G_B0
       0x1176c8000 -        0x11772bfff com.apple.AppleMetalOpenGLRenderer (1.0) <ed97217d-dbc3-3bd9-a531-e874ea072aa6> /System/Library/Extensions/AppleMetalOpenGLRenderer.bundle/Contents/MacOS/AppleMetalOpenGLRenderer
       0x18d738000 -        0x18d78ab4b libobjc.A.dylib (*) <ff1d8ae4-abef-35f1-a30a-1183b9cb414f> /usr/lib/libobjc.A.dylib
       0x19204f000 -        0x193771f9f com.apple.AppKit (6.9) <c92cc156-d767-322b-b79b-433f56e72561> /System/Library/Frameworks/AppKit.framework/Versions/C/AppKit
       0x280121000 -        0x280132edf com.apple.TextInputUIMac (1.0) <9c3fefc1-96d6-3c7e-9d20-b9926f6d2cb0> /System/Library/PrivateFrameworks/TextInputUIMacHelper.framework/Versions/A/TextInputUIMacHelper
       0x18d9e1000 -        0x18da2823f libdispatch.dylib (*) <f071efe4-299f-3089-acc4-0025b8ffb52a> /usr/lib/system/libdispatch.dylib
       0x1b7e75000 -        0x1b945dd3f com.apple.WebKit (21624) <49b21d99-8716-31b8-8686-71b287325f1d> /System/Library/Frameworks/WebKit.framework/Versions/A/WebKit
       0x1afa71000 -        0x1b15674ff com.apple.JavaScriptCore (21624) <1914f733-4af2-3ad7-9061-ca21ffc33841> /System/Library/Frameworks/JavaScriptCore.framework/Versions/A/JavaScriptCore
       0x18dbdd000 -        0x18e13b31f com.apple.CoreFoundation (6.9) <4bbd0da8-c600-3f3a-a38b-6664652fa04a> /System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation
       0x19a982000 -        0x19ac7d11f com.apple.HIToolbox (2.1.1) <8716490e-acc2-3688-8c2f-5ca42b4c9da9> /System/Library/Frameworks/Carbon.framework/Versions/A/Frameworks/HIToolbox.framework/Versions/A/HIToolbox
       0x18d7c0000 -        0x18d866217 dyld (*) <f924bdd3-4365-3466-9580-8b1b3fa8f857> /usr/lib/dyld
               0x0 - 0xffffffffffffffff ??? (*) <00000000-0000-0000-0000-000000000000> ???
       0x18db59000 -        0x18db962af libsystem_kernel.dylib (*) <fca53b98-3d6a-38b2-a0ec-df0f7e05f171> /usr/lib/system/libsystem_kernel.dylib
       0x18db97000 -        0x18dba3b3b libsystem_pthread.dylib (*) <4f33683c-18c8-39a1-800b-2e3bd43bcc13> /usr/lib/system/libsystem_pthread.dylib
       0x194361000 -        0x194384797 com.apple.TCC (1.0) <46ac4453-db23-3c07-a0eb-a68277a24098> /System/Library/PrivateFrameworks/TCC.framework/Versions/A/TCC
       0x18d86b000 -        0x18d8bf55f libxpc.dylib (*) <c40fcae8-7a17-3d82-87cb-3da4802adef1> /usr/lib/system/libxpc.dylib
       0x18f44a000 -        0x19042c41f com.apple.Foundation (6.9) <0c8c2a94-a688-3529-b2bb-4640df195105> /System/Library/Frameworks/Foundation.framework/Versions/C/Foundation
       0x198559000 -        0x1985d985f com.apple.CoreVideo (1.8) <8a36cb95-d65e-3838-8837-22fd9a7e3d9c> /System/Library/Frameworks/CoreVideo.framework/Versions/A/CoreVideo

External Modification Summary:
  Calls made by other processes targeting this process:
    task_for_pid: 0
    thread_create: 0
    thread_set_state: 0
  Calls made by this process:
    task_for_pid: 0
    thread_create: 0
    thread_set_state: 0
  Calls made by all processes on this machine:
    task_for_pid: 0
    thread_create: 0
    thread_set_state: 0

VM Region Summary:
ReadOnly portion of Libraries: Total=1.8G resident=0K(0%) swapped_out_or_unallocated=1.8G(100%)
Writable regions: Total=4.4G written=673K(0%) resident=673K(0%) swapped_out=0K(0%) unallocated=4.4G(100%)

                                VIRTUAL   REGION 
REGION TYPE                        SIZE    COUNT (non-coalesced) 
===========                     =======  ======= 
Accelerate framework               128K        1 
Activity Tracing                   256K        1 
AttributeGraph Data               1024K        1 
ColorSync                           32K        2 
CoreAnimation                      512K       31 
CoreGraphics                        64K        4 
CoreUI image data                  144K        2 
Foundation                          16K        1 
JS VM Gigacage (reserved)          4.0G        1         reserved VM address space (unallocated)
Kernel Alloc Once                   32K        1 
MALLOC                            57.4M       24 
MALLOC guard page                 3328K        4 
Memory Tag 22                     64.0M        1 
STACK GUARD                        416K       26 
Stack                             38.3M       27 
Stack Guard                       56.0M        1 
VM_ALLOCATE                        496K       23 
VM_ALLOCATE (reserved)            1536K       12         reserved VM address space (unallocated)
WebKit Malloc                    192.1M        5 
WebKit Malloc (reserved)          64.0M        1         reserved VM address space (unallocated)
__AUTH                            5998K      634 
__AUTH_CONST                      89.0M     1022 
__CTF                               824        1 
__DATA                            34.3M      975 
__DATA_CONST                      34.9M     1030 
__DATA_DIRTY                      8391K      880 
__FONT_DATA                        2352        1 
__GLSLBUILTINS                    5176K        1 
__LINKEDIT                       579.2M        5 
__OBJC_RO                         79.1M        1 
__OBJC_RW                         2598K        1 
__TEXT                             1.2G     1052 
__TPRO_CONST                       128K        2 
mapped file                      297.2M       44 
page table in kernel               673K        1 
shared memory                      864K       12 
===========                     =======  ======= 
TOTAL                              6.8G     5831 
TOTAL, minus reserved VM space     2.7G     5831 


-----------
Full Report
-----------

{"app_name":"kore-companion","timestamp":"2026-07-11 21:34:00.00 -0300","app_version":"0.1.0","slice_uuid":"0f7e9ca5-40a1-3f24-85f9-b7965689fb82","build_version":"0.1.0","platform":1,"bundleID":"com.kore.companion","share_with_app_devs":0,"is_first_party":0,"bug_type":"309","os_version":"macOS 26.5.2 (25F84)","roots_installed":0,"name":"kore-companion","incident_id":"2ECA8458-B5C9-4913-96AB-EDC9F06574EC"}
{
  "uptime" : 200000,
  "procRole" : "Foreground",
  "version" : 2,
  "userID" : 501,
  "deployVersion" : 210,
  "modelCode" : "Mac16,10",
  "coalitionID" : 38106,
  "osVersion" : {
    "train" : "macOS 26.5.2",
    "build" : "25F84",
    "releaseType" : "User"
  },
  "captureTime" : "2026-07-11 21:33:57.3252 -0300",
  "codeSigningMonitor" : 2,
  "incident" : "2ECA8458-B5C9-4913-96AB-EDC9F06574EC",
  "pid" : 87598,
  "translated" : false,
  "cpuType" : "ARM-64",
  "procLaunch" : "2026-07-11 21:33:56.9129 -0300",
  "procStartAbsTime" : 4952176294460,
  "procExitAbsTime" : 4952186106558,
  "procName" : "kore-companion",
  "procPath" : "\/Volumes\/VOLUME\/*\/kore-companion.app\/Contents\/MacOS\/kore-companion",
  "bundleInfo" : {"CFBundleShortVersionString":"0.1.0","CFBundleVersion":"0.1.0","CFBundleIdentifier":"com.kore.companion"},
  "storeInfo" : {"deviceIdentifierForVendor":"2A8D3E9C-8B07-5488-9747-D8F2D17E64A7","thirdParty":true},
  "parentProc" : "launchd",
  "parentPid" : 1,
  "coalitionName" : "com.kore.companion",
  "crashReporterKey" : "BDF41DE1-2765-3176-E799-80B9000A31CD",
  "appleIntelligenceStatus" : {"state":"unavailable","reasons":["selectedLanguageDoesNotMatchSelectedSiriLanguageInfo(system: en, siri: pt)","selectedLanguageDoesNotMatchSelectedSiriLanguage"]},
  "developerMode" : 1,
  "codeSigningID" : "kore_companion-8efdd83a6b37ca16",
  "codeSigningTeamID" : "",
  "codeSigningFlags" : 570556929,
  "codeSigningValidationCategory" : 10,
  "codeSigningTrustLevel" : 4294967295,
  "codeSigningAuxiliaryInfo" : 0,
  "instructionByteStream" : {"beforePC":"fyMD1f17v6n9AwCRwM7\/l78DAJH9e8Go\/w9f1sADX9YwQYDSARAA1A==","atPC":"AwEAVH8jA9X9e7+p\/QMAkbXO\/5e\/AwCR\/XvBqP8PX9bAA1\/WkDKA0g=="},
  "bootSessionUUID" : "E9AA3B4D-51A4-4153-8D31-40A30599E300",
  "sip" : "enabled",
  "exception" : {"codes":"0x0000000000000000, 0x0000000000000000","rawCodes":[0,0],"type":"EXC_CRASH","signal":"SIGABRT"},
  "termination" : {"flags":518,"code":0,"namespace":"TCC","details":["This app has crashed because it attempted to access privacy-sensitive data without a usage description. The app's Info.plist must contain an NSBluetoothAlwaysUsageDescription key with a string value explaining to the user how the app uses this data."]},
  "extMods" : {"caller":{"thread_create":0,"thread_set_state":0,"task_for_pid":0},"system":{"thread_create":0,"thread_set_state":0,"task_for_pid":0},"targeted":{"thread_create":0,"thread_set_state":0,"task_for_pid":0},"warnings":0},
  "faultingThread" : 7,
  "threads" : [{"threadState":{"x":[{"value":0},{"value":8720087358,"objc-selector":"currentContext"},{"value":11384599664,"symbolLocation":0,"symbol":"OBJC_CLASS_$_TUINSWindow"},{"value":18446726483666796544},{"value":4294967294},{"value":6128293368},{"value":6128293364},{"value":6128293352},{"value":8376971264},{"value":8720087358,"objc-selector":"currentContext"},{"value":40959497246},{"value":7},{"value":4},{"value":44954425648},{"value":8487154720,"symbolLocation":0,"symbol":"OBJC_METACLASS_$_NSGraphicsContext"},{"value":8487154720,"symbolLocation":0,"symbol":"OBJC_METACLASS_$_NSGraphicsContext"},{"value":6668181856,"symbolLocation":0,"symbol":"objc_autorelease"},{"value":8510076728},{"value":0},{"value":0},{"value":2},{"value":8044},{"value":44953122368},{"value":1},{"value":232},{"value":8487174144,"symbolLocation":64,"symbol":"OBJC_METACLASS_$_NSApplicationSceneWorkspace"},{"value":6746450912,"symbolLocation":0,"symbol":"-[NSWindow appearance]"},{"value":232},{"value":8371605504}],"flavor":"ARM_THREAD_STATE64","lr":{"value":6759288428},"cpsr":{"value":2147483648},"fp":{"value":6128296384},"sp":{"value":6128296352},"esr":{"value":2449473607,"description":"(Data Abort) byte write Translation fault"},"pc":{"value":6668182188},"far":{"value":0}},"id":4631537,"name":"main","queue":"com.apple.main-thread","frames":[{"imageOffset":58028,"symbol":"objc_autorelease","symbolLocation":332,"imageIndex":4},{"imageOffset":14524012,"symbol":"_NXCreateWindow","symbolLocation":564,"imageIndex":5},{"imageOffset":1210764,"symbol":"-[NSWindow _commonAwake]","symbolLocation":724,"imageIndex":5},{"imageOffset":306580,"symbol":"-[NSWindow _commonInitFrame:styleMask:backing:defer:]","symbolLocation":1044,"imageIndex":5},{"imageOffset":304400,"symbol":"-[NSWindow _initContent:styleMask:backing:defer:contentView:]","symbolLocation":848,"imageIndex":5},{"imageOffset":303540,"symbol":"-[NSWindow initWithContentRect:styleMask:backing:defer:]","symbolLocation":48,"imageIndex":5},{"imageOffset":13524,"symbol":"-[TUINSWindow init]","symbolLocation":80,"imageIndex":6},{"imageOffset":16372,"symbol":"-[TUINSCursorUIController init]","symbolLocation":268,"imageIndex":6},{"imageOffset":15988,"symbol":"__41+[TUINSCursorUIController sharedInstance]_block_invoke","symbolLocation":24,"imageIndex":6},{"imageOffset":111792,"symbol":"_dispatch_client_callout","symbolLocation":16,"imageIndex":7},{"imageOffset":17968,"symbol":"_dispatch_once_callout","symbolLocation":32,"imageIndex":7},{"imageOffset":15960,"symbol":"+[TUINSCursorUIController sharedInstance]","symbolLocation":84,"imageIndex":6},{"imageOffset":15623404,"symbol":"-[NSTextInputContext(NSTextInputContext_PrivateWebKitSupport) setShowsCursorAccessories:]","symbolLocation":36,"imageIndex":5},{"imageOffset":11177976,"symbol":"WebKit::WebViewImpl::selectionDidChange()","symbolLocation":200,"imageIndex":8},{"imageOffset":10917308,"symbol":"WebKit::PageClientImpl::selectionDidChange()","symbolLocation":52,"imageIndex":8},{"imageOffset":11104452,"symbol":"WebKit::WebPageProxy::didUpdateEditorState(WebKit::EditorState const&, WebKit::EditorState const&)","symbolLocation":320,"imageIndex":8},{"imageOffset":12807248,"symbol":"WebKit::WebPageProxy::updateEditorState(WebKit::EditorState&&, WebKit::WebPageProxy::ShouldMergeVisualEditorState)","symbolLocation":692,"imageIndex":8},{"imageOffset":9969952,"symbol":"WebKit::RemoteLayerTreeDrawingAreaProxy::commitLayerTree(IPC::Connection&, WebKit::RemoteLayerTreeCommitBundle const&, WTF::HashMap<WTF::ObjectIdentifierGeneric<WebKit::ImageBufferSetIdentifierType, WTF::ObjectIdentifierMainThreadAccessTraits<unsigned long long>, unsigned long long>, std::__1::unique_ptr<WebKit::BufferSetBackendHandle, std::__1::default_delete<WebKit::BufferSetBackendHandle>>, WTF::DefaultHash<WTF::ObjectIdentifierGeneric<WebKit::ImageBufferSetIdentifierType, WTF::ObjectIdentifierMainThreadAccessTraits<unsigned long long>, unsigned long long>>, WTF::HashTraits<WTF::ObjectIdentifierGeneric<WebKit::ImageBufferSetIdentifierType, WTF::ObjectIdentifierMainThreadAccessTraits<unsigned long long>, unsigned long long>>, WTF::HashTraits<std::__1::unique_ptr<WebKit::BufferSetBackendHandle, std::__1::default_delete<WebKit::BufferSetBackendHandle>>>, WTF::HashTableTraits, (WTF::ShouldValidateKey)1, WTF::FastMalloc>&&)","symbolLocation":848,"imageIndex":8},{"imageOffset":6098796,"symbol":"WebKit::RemoteLayerTreeDrawingAreaProxy::didReceiveMessage(IPC::Connection&, IPC::Decoder&)","symbolLocation":2028,"imageIndex":8},{"imageOffset":18944748,"symbol":"IPC::MessageReceiverMap::dispatchMessage(IPC::Connection&, IPC::Decoder&)","symbolLocation":348,"imageIndex":8},{"imageOffset":13341968,"symbol":"WebKit::WebProcessProxy::dispatchMessage(IPC::Connection&, IPC::Decoder&)","symbolLocation":44,"imageIndex":8},{"imageOffset":7175444,"symbol":"WebKit::WebProcessProxy::didReceiveMessage(IPC::Connection&, IPC::Decoder&)","symbolLocation":1036,"imageIndex":8},{"imageOffset":18774732,"symbol":"IPC::Connection::dispatchMessage(WTF::UniqueRef<IPC::Decoder>)","symbolLocation":324,"imageIndex":8},{"imageOffset":18775996,"symbol":"IPC::Connection::dispatchIncomingMessages()","symbolLocation":536,"imageIndex":8},{"imageOffset":2026528,"symbol":"WTF::RunLoop::performWork()","symbolLocation":460,"imageIndex":9},{"imageOffset":2032080,"symbol":"WTF::RunLoop::performWork(void*)","symbolLocation":36,"imageIndex":9},{"imageOffset":515888,"symbol":"__CFRUNLOOP_IS_CALLING_OUT_TO_A_SOURCE0_PERFORM_FUNCTION__","symbolLocation":28,"imageIndex":10},{"imageOffset":515780,"symbol":"__CFRunLoopDoSource0","symbolLocation":172,"imageIndex":10},{"imageOffset":515120,"symbol":"__CFRunLoopDoSources0","symbolLocation":232,"imageIndex":10},{"imageOffset":510036,"symbol":"__CFRunLoopRun","symbolLocation":820,"imageIndex":10},{"imageOffset":1372612,"symbol":"_CFRunLoopRunSpecificWithOptions","symbolLocation":532,"imageIndex":10},{"imageOffset":775520,"symbol":"RunCurrentEventLoopInMode","symbolLocation":320,"imageIndex":11},{"imageOffset":788668,"symbol":"ReceiveNextEventCommon","symbolLocation":488,"imageIndex":11},{"imageOffset":2400588,"symbol":"_BlockUntilNextEventMatchingListInMode","symbolLocation":48,"imageIndex":11},{"imageOffset":7230300,"symbol":"_DPSBlockUntilNextEventMatchingListInMode","symbolLocation":228,"imageIndex":5},{"imageOffset":233604,"symbol":"_DPSNextEvent","symbolLocation":576,"imageIndex":5},{"imageOffset":12380336,"symbol":"-[NSApplication(NSEventRouting) _nextEventMatchingEventMask:untilDate:inMode:dequeue:]","symbolLocation":688,"imageIndex":5},{"imageOffset":12379580,"symbol":"-[NSApplication(NSEventRouting) nextEventMatchingMask:untilDate:inMode:dequeue:]","symbolLocation":72,"imageIndex":5},{"imageOffset":180540,"symbol":"-[NSApplication run]","symbolLocation":368,"imageIndex":5},{"imageOffset":2806480,"symbol":"tao::platform_impl::platform::event_loop::EventLoop$LT$T$GT$::run::h17b652263bbd06ee","symbolLocation":512,"imageIndex":0},{"imageOffset":2930432,"symbol":"_$LT$tauri_runtime_wry..Wry$LT$T$GT$$u20$as$u20$tauri_runtime..Runtime$LT$T$GT$$GT$::run::hf3de48ef026a32db","symbolLocation":328,"imageIndex":0},{"imageOffset":1676896,"symbol":"kore_companion_lib::run::heeee3927d1ed827a","symbolLocation":9584,"imageIndex":0},{"imageOffset":6068,"symbol":"std::sys::backtrace::__rust_begin_short_backtrace::h57ca893ef5a3d214","symbolLocation":12,"imageIndex":0},{"imageOffset":6044,"symbol":"std::rt::lang_start::_$u7b$$u7b$closure$u7d$$u7d$::hd712266dd296f15d","symbolLocation":16,"imageIndex":0},{"imageOffset":6727112,"symbol":"_RNvNtCsaLOjE9VYtxK_3std2rt19lang_start_internal","symbolLocation":952,"imageIndex":0},{"imageOffset":6156,"symbol":"main","symbolLocation":52,"imageIndex":0},{"imageOffset":130560,"symbol":"start","symbolLocation":6992,"imageIndex":12}]},{"id":4631555,"frames":[],"threadState":{"x":[{"value":6128889856},{"value":8451},{"value":6128353280},{"value":0},{"value":409604},{"value":18446744073709551615},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0}],"flavor":"ARM_THREAD_STATE64","lr":{"value":0},"cpsr":{"value":0},"fp":{"value":0},"sp":{"value":6128889856},"esr":{"value":1442840704,"description":"(Syscall)"},"pc":{"value":6672714760},"far":{"value":0}}},{"id":4631556,"frames":[],"threadState":{"x":[{"value":6129463296},{"value":9475},{"value":6128926720},{"value":0},{"value":409604},{"value":18446744073709551615},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0}],"flavor":"ARM_THREAD_STATE64","lr":{"value":0},"cpsr":{"value":0},"fp":{"value":0},"sp":{"value":6129463296},"esr":{"value":1442840704,"description":"(Syscall)"},"pc":{"value":6672714760},"far":{"value":0}}},{"id":4631564,"frames":[],"threadState":{"x":[{"value":6130036736},{"value":19715},{"value":6129500160},{"value":0},{"value":409604},{"value":18446744073709551615},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0}],"flavor":"ARM_THREAD_STATE64","lr":{"value":0},"cpsr":{"value":0},"fp":{"value":0},"sp":{"value":6130036736},"esr":{"value":1442840704,"description":"(Syscall)"},"pc":{"value":6672714760},"far":{"value":0}}},{"id":4631572,"name":"com.apple.NSEventThread","threadState":{"x":[{"value":268451845},{"value":21592279046},{"value":8589934592},{"value":133053791862784},{"value":0},{"value":133053791862784},{"value":2},{"value":4294967295},{"value":0},{"value":17179869184},{"value":0},{"value":2},{"value":0},{"value":0},{"value":30979},{"value":0},{"value":18446744073709551569},{"value":8510125976},{"value":0},{"value":4294967295},{"value":2},{"value":133053791862784},{"value":0},{"value":133053791862784},{"value":21592279046},{"value":6130606216},{"value":8589934592},{"value":18446744073709550527},{"value":4412409862}],"flavor":"ARM_THREAD_STATE64","lr":{"value":6672532852},"cpsr":{"value":0},"fp":{"value":6130606064},"sp":{"value":6130605984},"esr":{"value":1442840704,"description":"(Syscall)"},"pc":{"value":6672456756},"far":{"value":0}},"frames":[{"imageOffset":3124,"symbol":"mach_msg2_trap","symbolLocation":8,"imageIndex":14},{"imageOffset":79220,"symbol":"mach_msg2_internal","symbolLocation":76,"imageIndex":14},{"imageOffset":39360,"symbol":"mach_msg_overwrite","symbolLocation":480,"imageIndex":14},{"imageOffset":4032,"symbol":"mach_msg","symbolLocation":24,"imageIndex":14},{"imageOffset":516312,"symbol":"__CFRunLoopServiceMachPort","symbolLocation":160,"imageIndex":10},{"imageOffset":510404,"symbol":"__CFRunLoopRun","symbolLocation":1188,"imageIndex":10},{"imageOffset":1372612,"symbol":"_CFRunLoopRunSpecificWithOptions","symbolLocation":532,"imageIndex":10},{"imageOffset":1420412,"symbol":"_NSEventThread","symbolLocation":184,"imageIndex":5},{"imageOffset":27736,"symbol":"_pthread_start","symbolLocation":136,"imageIndex":15},{"imageOffset":7196,"symbol":"thread_start","symbolLocation":8,"imageIndex":15}]},{"id":4631586,"name":"JavaScriptCore libpas scavenger","threadState":{"x":[{"value":260},{"value":0},{"value":0},{"value":0},{"value":0},{"value":160},{"value":0},{"value":99999088},{"value":6131183272},{"value":0},{"value":0},{"value":2},{"value":2},{"value":0},{"value":0},{"value":0},{"value":305},{"value":8510124096},{"value":0},{"value":4804651072},{"value":4804651136},{"value":6131183840},{"value":99999088},{"value":0},{"value":0},{"value":513},{"value":768},{"value":0},{"value":8489476096,"symbolLocation":3504,"symbol":"bmalloc_common_primitive_heap_support"}],"flavor":"ARM_THREAD_STATE64","lr":{"value":6672736552},"cpsr":{"value":1610612736},"fp":{"value":6131183392},"sp":{"value":6131183248},"esr":{"value":1442840704,"description":"(Syscall)"},"pc":{"value":6672471308},"far":{"value":0}},"frames":[{"imageOffset":17676,"symbol":"__psynch_cvwait","symbolLocation":8,"imageIndex":14},{"imageOffset":28968,"symbol":"_pthread_cond_wait","symbolLocation":980,"imageIndex":15},{"imageOffset":26058940,"symbol":"scavenger_thread_main","symbolLocation":1416,"imageIndex":9},{"imageOffset":27736,"symbol":"_pthread_start","symbolLocation":136,"imageIndex":15},{"imageOffset":7196,"symbol":"thread_start","symbolLocation":8,"imageIndex":15}]},{"id":4631600,"frames":[],"threadState":{"x":[{"value":6131757056},{"value":54275},{"value":6131220480},{"value":0},{"value":409604},{"value":18446744073709551615},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0}],"flavor":"ARM_THREAD_STATE64","lr":{"value":0},"cpsr":{"value":0},"fp":{"value":0},"sp":{"value":6131757056},"esr":{"value":1442840704,"description":"(Syscall)"},"pc":{"value":6672714760},"far":{"value":0}}},{"triggered":true,"id":4631601,"threadState":{"x":[{"value":11},{"value":0},{"value":44936155696},{"value":34},{"value":44936155748},{"value":0},{"value":70650219223712034},{"value":6132330720},{"value":32},{"value":12823935159507812400},{"value":72057598332895232},{"value":4631601},{"value":490154836223135748},{"value":144115192639261856},{"value":2199023259648},{"value":144115188344294256},{"value":521},{"value":8510124424},{"value":0},{"value":0},{"value":44936155748},{"value":34},{"value":44936155696},{"value":0},{"value":11},{"value":44941864960},{"value":0},{"value":0},{"value":0}],"flavor":"ARM_THREAD_STATE64","lr":{"value":6672670952},"cpsr":{"value":1073741824},"fp":{"value":6132327984},"sp":{"value":6132327920},"esr":{"value":1442840704,"description":"(Syscall)"},"pc":{"value":6672509712,"matchesCrashFrame":1},"far":{"value":0}},"queue":"com.apple.root.default-qos","frames":[{"imageOffset":56080,"symbol":"__abort_with_payload","symbolLocation":8,"imageIndex":14},{"imageOffset":217320,"symbol":"abort_with_payload_wrapper_internal","symbolLocation":104,"imageIndex":14},{"imageOffset":217372,"symbol":"abort_with_payload","symbolLocation":16,"imageIndex":14},{"imageOffset":20208,"symbol":"__TCC_CRASHING_DUE_TO_PRIVACY_VIOLATION__","symbolLocation":172,"imageIndex":16},{"imageOffset":22588,"symbol":"__TCCAccessRequest_block_invoke.229","symbolLocation":628,"imageIndex":16},{"imageOffset":10284,"symbol":"__tccd_send_message_block_invoke","symbolLocation":632,"imageIndex":16},{"imageOffset":64512,"symbol":"_xpc_connection_reply_callout","symbolLocation":120,"imageIndex":17},{"imageOffset":64248,"symbol":"_xpc_connection_call_reply_async","symbolLocation":96,"imageIndex":17},{"imageOffset":111840,"symbol":"<deduplicated_symbol>","symbolLocation":16,"imageIndex":7},{"imageOffset":128300,"symbol":"_dispatch_mach_msg_async_reply_invoke","symbolLocation":340,"imageIndex":7},{"imageOffset":84804,"symbol":"_dispatch_root_queue_drain_deferred_item","symbolLocation":216,"imageIndex":7},{"imageOffset":82832,"symbol":"_dispatch_kevent_worker_thread","symbolLocation":536,"imageIndex":7},{"imageOffset":12024,"symbol":"_pthread_wqthread","symbolLocation":348,"imageIndex":15},{"imageOffset":7184,"symbol":"start_wqthread","symbolLocation":8,"imageIndex":15}]},{"id":4631602,"name":"WebCore: Scrolling","threadState":{"x":[{"value":268451845},{"value":21592279046},{"value":8589934592},{"value":227611791851520},{"value":0},{"value":227611791851520},{"value":2},{"value":4294967295},{"value":0},{"value":17179869184},{"value":0},{"value":2},{"value":0},{"value":0},{"value":52995},{"value":0},{"value":18446744073709551569},{"value":8510125976},{"value":0},{"value":4294967295},{"value":2},{"value":227611791851520},{"value":0},{"value":227611791851520},{"value":21592279046},{"value":6132899784},{"value":8589934592},{"value":18446744073709550527},{"value":4412409862}],"flavor":"ARM_THREAD_STATE64","lr":{"value":6672532852},"cpsr":{"value":0},"fp":{"value":6132899632},"sp":{"value":6132899552},"esr":{"value":1442840704,"description":"(Syscall)"},"pc":{"value":6672456756},"far":{"value":0}},"frames":[{"imageOffset":3124,"symbol":"mach_msg2_trap","symbolLocation":8,"imageIndex":14},{"imageOffset":79220,"symbol":"mach_msg2_internal","symbolLocation":76,"imageIndex":14},{"imageOffset":39360,"symbol":"mach_msg_overwrite","symbolLocation":480,"imageIndex":14},{"imageOffset":4032,"symbol":"mach_msg","symbolLocation":24,"imageIndex":14},{"imageOffset":516312,"symbol":"__CFRunLoopServiceMachPort","symbolLocation":160,"imageIndex":10},{"imageOffset":510404,"symbol":"__CFRunLoopRun","symbolLocation":1188,"imageIndex":10},{"imageOffset":1372612,"symbol":"_CFRunLoopRunSpecificWithOptions","symbolLocation":532,"imageIndex":10},{"imageOffset":994036,"symbol":"CFRunLoopRun","symbolLocation":64,"imageIndex":10},{"imageOffset":2029528,"symbol":"WTF::Detail::CallableWrapper<WTF::RunLoop::create(WTF::ASCIILiteral, WTF::ThreadType, WTF::Thread::QOS)::$_0, void>::call()","symbolLocation":244,"imageIndex":9},{"imageOffset":2323588,"symbol":"WTF::Thread::entryPoint(WTF::Thread::NewThreadContext*)","symbolLocation":300,"imageIndex":9},{"imageOffset":24712,"symbol":"WTF::wtfThreadEntryPoint(void*)","symbolLocation":16,"imageIndex":9},{"imageOffset":27736,"symbol":"_pthread_start","symbolLocation":136,"imageIndex":15},{"imageOffset":7196,"symbol":"thread_start","symbolLocation":8,"imageIndex":15}]},{"id":4631603,"threadState":{"x":[{"value":268451845},{"value":21592279046},{"value":8589934592},{"value":293582489518080},{"value":0},{"value":293582489518080},{"value":2},{"value":4294967295},{"value":0},{"value":17179869184},{"value":0},{"value":2},{"value":0},{"value":0},{"value":68355},{"value":0},{"value":18446744073709551569},{"value":8510125976},{"value":0},{"value":4294967295},{"value":2},{"value":293582489518080},{"value":0},{"value":293582489518080},{"value":21592279046},{"value":6133473016},{"value":8589934592},{"value":18446744073709550527},{"value":4412409862}],"flavor":"ARM_THREAD_STATE64","lr":{"value":6672532852},"cpsr":{"value":0},"fp":{"value":6133472864},"sp":{"value":6133472784},"esr":{"value":1442840704,"description":"(Syscall)"},"pc":{"value":6672456756},"far":{"value":0}},"queue":"com.apple.root.user-interactive-qos","frames":[{"imageOffset":3124,"symbol":"mach_msg2_trap","symbolLocation":8,"imageIndex":14},{"imageOffset":79220,"symbol":"mach_msg2_internal","symbolLocation":76,"imageIndex":14},{"imageOffset":39360,"symbol":"mach_msg_overwrite","symbolLocation":480,"imageIndex":14},{"imageOffset":4032,"symbol":"mach_msg","symbolLocation":24,"imageIndex":14},{"imageOffset":516312,"symbol":"__CFRunLoopServiceMachPort","symbolLocation":160,"imageIndex":10},{"imageOffset":510404,"symbol":"__CFRunLoopRun","symbolLocation":1188,"imageIndex":10},{"imageOffset":1372612,"symbol":"_CFRunLoopRunSpecificWithOptions","symbolLocation":532,"imageIndex":10},{"imageOffset":367428,"symbol":"-[NSRunLoop(NSRunLoop) runMode:beforeDate:]","symbolLocation":212,"imageIndex":18},{"imageOffset":8433868,"symbol":"-[NSAnimation _runBlocking]","symbolLocation":412,"imageIndex":5},{"imageOffset":6696,"symbol":"_dispatch_call_block_and_release","symbolLocation":32,"imageIndex":7},{"imageOffset":111792,"symbol":"_dispatch_client_callout","symbolLocation":16,"imageIndex":7},{"imageOffset":232812,"symbol":"<deduplicated_symbol>","symbolLocation":28,"imageIndex":7},{"imageOffset":80604,"symbol":"_dispatch_root_queue_drain","symbolLocation":708,"imageIndex":7},{"imageOffset":82208,"symbol":"_dispatch_worker_thread2","symbolLocation":184,"imageIndex":7},{"imageOffset":11908,"symbol":"_pthread_wqthread","symbolLocation":232,"imageIndex":15},{"imageOffset":7184,"symbol":"start_wqthread","symbolLocation":8,"imageIndex":15}]},{"id":4631670,"name":"CVDisplayLink","threadState":{"x":[{"value":260},{"value":0},{"value":0},{"value":0},{"value":0},{"value":65704},{"value":0},{"value":15652792},{"value":2561},{"value":0},{"value":0},{"value":2},{"value":2},{"value":0},{"value":0},{"value":0},{"value":305},{"value":8510124096},{"value":0},{"value":44940692536},{"value":44940692600},{"value":1},{"value":15652792},{"value":0},{"value":0},{"value":2561},{"value":2816},{"value":8444180824,"symbolLocation":0,"symbol":"kZeroVideoTime"},{"value":4952186350688}],"flavor":"ARM_THREAD_STATE64","lr":{"value":6672736596},"cpsr":{"value":2684354560},"fp":{"value":6134050224},"sp":{"value":6134050080},"esr":{"value":1442840704,"description":"(Syscall)"},"pc":{"value":6672471308},"far":{"value":0}},"frames":[{"imageOffset":17676,"symbol":"__psynch_cvwait","symbolLocation":8,"imageIndex":14},{"imageOffset":29012,"symbol":"_pthread_cond_wait","symbolLocation":1024,"imageIndex":15},{"imageOffset":15172,"symbol":"CVDisplayLink::waitUntil(unsigned long long)","symbolLocation":336,"imageIndex":19},{"imageOffset":11308,"symbol":"CVDisplayLink::runIOThread()","symbolLocation":452,"imageIndex":19},{"imageOffset":27736,"symbol":"_pthread_start","symbolLocation":136,"imageIndex":15},{"imageOffset":7196,"symbol":"thread_start","symbolLocation":8,"imageIndex":15}]},{"id":4631671,"name":"CVDisplayLink","threadState":{"x":[{"value":260},{"value":0},{"value":0},{"value":0},{"value":0},{"value":65704},{"value":0},{"value":15649958},{"value":2561},{"value":0},{"value":0},{"value":2},{"value":2},{"value":0},{"value":0},{"value":0},{"value":305},{"value":8510124096},{"value":0},{"value":44940689464},{"value":44940689528},{"value":1},{"value":15649958},{"value":0},{"value":0},{"value":2561},{"value":2816},{"value":8444180824,"symbolLocation":0,"symbol":"kZeroVideoTime"},{"value":4952186350688}],"flavor":"ARM_THREAD_STATE64","lr":{"value":6672736596},"cpsr":{"value":2684354560},"fp":{"value":6134623664},"sp":{"value":6134623520},"esr":{"value":1442840704,"description":"(Syscall)"},"pc":{"value":6672471308},"far":{"value":0}},"frames":[{"imageOffset":17676,"symbol":"__psynch_cvwait","symbolLocation":8,"imageIndex":14},{"imageOffset":29012,"symbol":"_pthread_cond_wait","symbolLocation":1024,"imageIndex":15},{"imageOffset":15172,"symbol":"CVDisplayLink::waitUntil(unsigned long long)","symbolLocation":336,"imageIndex":19},{"imageOffset":11308,"symbol":"CVDisplayLink::runIOThread()","symbolLocation":452,"imageIndex":19},{"imageOffset":27736,"symbol":"_pthread_start","symbolLocation":136,"imageIndex":15},{"imageOffset":7196,"symbol":"thread_start","symbolLocation":8,"imageIndex":15}]},{"id":4631672,"name":"tokio-rt-worker","threadState":{"x":[{"value":260},{"value":0},{"value":256},{"value":0},{"value":0},{"value":160},{"value":0},{"value":0},{"value":6136768136},{"value":0},{"value":0},{"value":2},{"value":2},{"value":0},{"value":0},{"value":0},{"value":305},{"value":8510124096},{"value":0},{"value":44941297136},{"value":44941297200},{"value":6136770784},{"value":0},{"value":0},{"value":256},{"value":257},{"value":512},{"value":11400714819323198485},{"value":4349323544,"symbolLocation":0,"symbol":"parking_lot_core::parking_lot::HASHTABLE::h76c7a5179771e417"}],"flavor":"ARM_THREAD_STATE64","lr":{"value":6672736552},"cpsr":{"value":1610612736},"fp":{"value":6136768256},"sp":{"value":6136768112},"esr":{"value":1442840704,"description":"(Syscall)"},"pc":{"value":6672471308},"far":{"value":0}},"frames":[{"imageOffset":17676,"symbol":"__psynch_cvwait","symbolLocation":8,"imageIndex":14},{"imageOffset":28968,"symbol":"_pthread_cond_wait","symbolLocation":980,"imageIndex":15},{"imageOffset":5512976,"symbol":"parking_lot::condvar::Condvar::wait_until_internal::h7a8073d8c6fc70c3","symbolLocation":552,"imageIndex":0},{"imageOffset":5372784,"symbol":"tokio::runtime::scheduler::multi_thread::park::Inner::park_condvar::h7554bf8664fac1d7","symbolLocation":208,"imageIndex":0},{"imageOffset":5396536,"symbol":"tokio::runtime::scheduler::multi_thread::worker::Context::park_internal::h467e864812df67f8","symbolLocation":384,"imageIndex":0},{"imageOffset":5401184,"symbol":"tokio::runtime::scheduler::multi_thread::worker::Context::run::h3f04c0f91a4668a3","symbolLocation":3712,"imageIndex":0},{"imageOffset":5489348,"symbol":"tokio::runtime::context::scoped::Scoped$LT$T$GT$::set::h3b819941c9378206","symbolLocation":56,"imageIndex":0},{"imageOffset":5372108,"symbol":"tokio::runtime::context::runtime::enter_runtime::hed6f538e124ba00c","symbolLocation":492,"imageIndex":0},{"imageOffset":5390180,"symbol":"tokio::runtime::scheduler::multi_thread::worker::run::h750c64c6ac0235a6","symbolLocation":176,"imageIndex":0},{"imageOffset":5428896,"symbol":"_$LT$tokio..runtime..blocking..task..BlockingTask$LT$T$GT$$u20$as$u20$core..future..future..Future$GT$::poll::h28847489b1106f55","symbolLocation":108,"imageIndex":0},{"imageOffset":5449248,"symbol":"tokio::runtime::task::core::Core$LT$T$C$S$GT$::poll::h06297f738cd993bf","symbolLocation":164,"imageIndex":0},{"imageOffset":5366344,"symbol":"tokio::runtime::task::harness::Harness$LT$T$C$S$GT$::poll::h494a0f555e1b52e9","symbolLocation":168,"imageIndex":0},{"imageOffset":5443456,"symbol":"tokio::runtime::blocking::pool::Inner::run::h69fc3caa6bb155fa","symbolLocation":260,"imageIndex":0},{"imageOffset":5405316,"symbol":"std::sys::backtrace::__rust_begin_short_backtrace::h3711ebb41b529b4e","symbolLocation":224,"imageIndex":0},{"imageOffset":5407388,"symbol":"core::ops::function::FnOnce::call_once$u7b$$u7b$vtable.shim$u7d$$u7d$::h5b590e309155afbc","symbolLocation":92,"imageIndex":0},{"imageOffset":6756720,"symbol":"_RNvNvMs0_NtNtNtCsaLOjE9VYtxK_3std3sys6thread4unixNtB7_6Thread3new12thread_start","symbolLocation":408,"imageIndex":0},{"imageOffset":27736,"symbol":"_pthread_start","symbolLocation":136,"imageIndex":15},{"imageOffset":7196,"symbol":"thread_start","symbolLocation":8,"imageIndex":15}]},{"id":4631673,"name":"tokio-rt-worker","threadState":{"x":[{"value":260},{"value":0},{"value":256},{"value":0},{"value":0},{"value":160},{"value":0},{"value":0},{"value":6138914440},{"value":0},{"value":0},{"value":2},{"value":2},{"value":0},{"value":0},{"value":0},{"value":305},{"value":8510124096},{"value":0},{"value":44941298032},{"value":44941298096},{"value":6138917088},{"value":0},{"value":0},{"value":256},{"value":257},{"value":512},{"value":11400714819323198485},{"value":4349323544,"symbolLocation":0,"symbol":"parking_lot_core::parking_lot::HASHTABLE::h76c7a5179771e417"}],"flavor":"ARM_THREAD_STATE64","lr":{"value":6672736552},"cpsr":{"value":1610612736},"fp":{"value":6138914560},"sp":{"value":6138914416},"esr":{"value":1442840704,"description":"(Syscall)"},"pc":{"value":6672471308},"far":{"value":0}},"frames":[{"imageOffset":17676,"symbol":"__psynch_cvwait","symbolLocation":8,"imageIndex":14},{"imageOffset":28968,"symbol":"_pthread_cond_wait","symbolLocation":980,"imageIndex":15},{"imageOffset":5512976,"symbol":"parking_lot::condvar::Condvar::wait_until_internal::h7a8073d8c6fc70c3","symbolLocation":552,"imageIndex":0},{"imageOffset":5372784,"symbol":"tokio::runtime::scheduler::multi_thread::park::Inner::park_condvar::h7554bf8664fac1d7","symbolLocation":208,"imageIndex":0},{"imageOffset":5396536,"symbol":"tokio::runtime::scheduler::multi_thread::worker::Context::park_internal::h467e864812df67f8","symbolLocation":384,"imageIndex":0},{"imageOffset":5401184,"symbol":"tokio::runtime::scheduler::multi_thread::worker::Context::run::h3f04c0f91a4668a3","symbolLocation":3712,"imageIndex":0},{"imageOffset":5489348,"symbol":"tokio::runtime::context::scoped::Scoped$LT$T$GT$::set::h3b819941c9378206","symbolLocation":56,"imageIndex":0},{"imageOffset":5372108,"symbol":"tokio::runtime::context::runtime::enter_runtime::hed6f538e124ba00c","symbolLocation":492,"imageIndex":0},{"imageOffset":5390180,"symbol":"tokio::runtime::scheduler::multi_thread::worker::run::h750c64c6ac0235a6","symbolLocation":176,"imageIndex":0},{"imageOffset":5428896,"symbol":"_$LT$tokio..runtime..blocking..task..BlockingTask$LT$T$GT$$u20$as$u20$core..future..future..Future$GT$::poll::h28847489b1106f55","symbolLocation":108,"imageIndex":0},{"imageOffset":5449248,"symbol":"tokio::runtime::task::core::Core$LT$T$C$S$GT$::poll::h06297f738cd993bf","symbolLocation":164,"imageIndex":0},{"imageOffset":5366344,"symbol":"tokio::runtime::task::harness::Harness$LT$T$C$S$GT$::poll::h494a0f555e1b52e9","symbolLocation":168,"imageIndex":0},{"imageOffset":5443456,"symbol":"tokio::runtime::blocking::pool::Inner::run::h69fc3caa6bb155fa","symbolLocation":260,"imageIndex":0},{"imageOffset":5405316,"symbol":"std::sys::backtrace::__rust_begin_short_backtrace::h3711ebb41b529b4e","symbolLocation":224,"imageIndex":0},{"imageOffset":5407388,"symbol":"core::ops::function::FnOnce::call_once$u7b$$u7b$vtable.shim$u7d$$u7d$::h5b590e309155afbc","symbolLocation":92,"imageIndex":0},{"imageOffset":6756720,"symbol":"_RNvNvMs0_NtNtNtCsaLOjE9VYtxK_3std3sys6thread4unixNtB7_6Thread3new12thread_start","symbolLocation":408,"imageIndex":0},{"imageOffset":27736,"symbol":"_pthread_start","symbolLocation":136,"imageIndex":15},{"imageOffset":7196,"symbol":"thread_start","symbolLocation":8,"imageIndex":15}]},{"id":4631674,"name":"tokio-rt-worker","threadState":{"x":[{"value":4},{"value":0},{"value":0},{"value":44935086080},{"value":1024},{"value":0},{"value":224},{"value":6141061168},{"value":0},{"value":6141061168},{"value":0},{"value":2},{"value":44960840512},{"value":10},{"value":4},{"value":0},{"value":363},{"value":8510125816},{"value":0},{"value":44946771352},{"value":1000000000},{"value":1000000000},{"value":1000000000},{"value":1000000000},{"value":1000000000},{"value":6141061544},{"value":0},{"value":3970518594},{"value":1000000000}],"flavor":"ARM_THREAD_STATE64","lr":{"value":4344057792},"cpsr":{"value":1610612736},"fp":{"value":6141061200},"sp":{"value":6141061152},"esr":{"value":1442840704,"description":"(Syscall)"},"pc":{"value":6672482244},"far":{"value":0}},"frames":[{"imageOffset":28612,"symbol":"kevent","symbolLocation":8,"imageIndex":14},{"imageOffset":5509056,"symbol":"mio::poll::Poll::poll::hb33eea066d8918e1","symbolLocation":116,"imageIndex":0},{"imageOffset":5425484,"symbol":"tokio::runtime::io::driver::Driver::turn::hcbb9c32ac53bf1a6","symbolLocation":120,"imageIndex":0},{"imageOffset":5482768,"symbol":"tokio::runtime::time::Driver::park_internal::h257995291f8c752e","symbolLocation":740,"imageIndex":0},{"imageOffset":5396392,"symbol":"tokio::runtime::scheduler::multi_thread::worker::Context::park_internal::h467e864812df67f8","symbolLocation":240,"imageIndex":0},{"imageOffset":5401184,"symbol":"tokio::runtime::scheduler::multi_thread::worker::Context::run::h3f04c0f91a4668a3","symbolLocation":3712,"imageIndex":0},{"imageOffset":5489348,"symbol":"tokio::runtime::context::scoped::Scoped$LT$T$GT$::set::h3b819941c9378206","symbolLocation":56,"imageIndex":0},{"imageOffset":5372108,"symbol":"tokio::runtime::context::runtime::enter_runtime::hed6f538e124ba00c","symbolLocation":492,"imageIndex":0},{"imageOffset":5390180,"symbol":"tokio::runtime::scheduler::multi_thread::worker::run::h750c64c6ac0235a6","symbolLocation":176,"imageIndex":0},{"imageOffset":5428896,"symbol":"_$LT$tokio..runtime..blocking..task..BlockingTask$LT$T$GT$$u20$as$u20$core..future..future..Future$GT$::poll::h28847489b1106f55","symbolLocation":108,"imageIndex":0},{"imageOffset":5449248,"symbol":"tokio::runtime::task::core::Core$LT$T$C$S$GT$::poll::h06297f738cd993bf","symbolLocation":164,"imageIndex":0},{"imageOffset":5366344,"symbol":"tokio::runtime::task::harness::Harness$LT$T$C$S$GT$::poll::h494a0f555e1b52e9","symbolLocation":168,"imageIndex":0},{"imageOffset":5443456,"symbol":"tokio::runtime::blocking::pool::Inner::run::h69fc3caa6bb155fa","symbolLocation":260,"imageIndex":0},{"imageOffset":5405316,"symbol":"std::sys::backtrace::__rust_begin_short_backtrace::h3711ebb41b529b4e","symbolLocation":224,"imageIndex":0},{"imageOffset":5407388,"symbol":"core::ops::function::FnOnce::call_once$u7b$$u7b$vtable.shim$u7d$$u7d$::h5b590e309155afbc","symbolLocation":92,"imageIndex":0},{"imageOffset":6756720,"symbol":"_RNvNvMs0_NtNtNtCsaLOjE9VYtxK_3std3sys6thread4unixNtB7_6Thread3new12thread_start","symbolLocation":408,"imageIndex":0},{"imageOffset":27736,"symbol":"_pthread_start","symbolLocation":136,"imageIndex":15},{"imageOffset":7196,"symbol":"thread_start","symbolLocation":8,"imageIndex":15}]},{"id":4631675,"name":"tokio-rt-worker","threadState":{"x":[{"value":260},{"value":0},{"value":2048},{"value":0},{"value":0},{"value":160},{"value":0},{"value":0},{"value":6143207048},{"value":0},{"value":0},{"value":2},{"value":2},{"value":0},{"value":0},{"value":0},{"value":305},{"value":8510124096},{"value":0},{"value":44941298928},{"value":44941298992},{"value":6143209696},{"value":0},{"value":0},{"value":2048},{"value":2049},{"value":2304},{"value":11400714819323198485},{"value":4349323544,"symbolLocation":0,"symbol":"parking_lot_core::parking_lot::HASHTABLE::h76c7a5179771e417"}],"flavor":"ARM_THREAD_STATE64","lr":{"value":6672736552},"cpsr":{"value":1610612736},"fp":{"value":6143207168},"sp":{"value":6143207024},"esr":{"value":1442840704,"description":"(Syscall)"},"pc":{"value":6672471308},"far":{"value":0}},"frames":[{"imageOffset":17676,"symbol":"__psynch_cvwait","symbolLocation":8,"imageIndex":14},{"imageOffset":28968,"symbol":"_pthread_cond_wait","symbolLocation":980,"imageIndex":15},{"imageOffset":5512976,"symbol":"parking_lot::condvar::Condvar::wait_until_internal::h7a8073d8c6fc70c3","symbolLocation":552,"imageIndex":0},{"imageOffset":5372784,"symbol":"tokio::runtime::scheduler::multi_thread::park::Inner::park_condvar::h7554bf8664fac1d7","symbolLocation":208,"imageIndex":0},{"imageOffset":5396536,"symbol":"tokio::runtime::scheduler::multi_thread::worker::Context::park_internal::h467e864812df67f8","symbolLocation":384,"imageIndex":0},{"imageOffset":5401184,"symbol":"tokio::runtime::scheduler::multi_thread::worker::Context::run::h3f04c0f91a4668a3","symbolLocation":3712,"imageIndex":0},{"imageOffset":5489348,"symbol":"tokio::runtime::context::scoped::Scoped$LT$T$GT$::set::h3b819941c9378206","symbolLocation":56,"imageIndex":0},{"imageOffset":5372108,"symbol":"tokio::runtime::context::runtime::enter_runtime::hed6f538e124ba00c","symbolLocation":492,"imageIndex":0},{"imageOffset":5390180,"symbol":"tokio::runtime::scheduler::multi_thread::worker::run::h750c64c6ac0235a6","symbolLocation":176,"imageIndex":0},{"imageOffset":5428896,"symbol":"_$LT$tokio..runtime..blocking..task..BlockingTask$LT$T$GT$$u20$as$u20$core..future..future..Future$GT$::poll::h28847489b1106f55","symbolLocation":108,"imageIndex":0},{"imageOffset":5449248,"symbol":"tokio::runtime::task::core::Core$LT$T$C$S$GT$::poll::h06297f738cd993bf","symbolLocation":164,"imageIndex":0},{"imageOffset":5366344,"symbol":"tokio::runtime::task::harness::Harness$LT$T$C$S$GT$::poll::h494a0f555e1b52e9","symbolLocation":168,"imageIndex":0},{"imageOffset":5443456,"symbol":"tokio::runtime::blocking::pool::Inner::run::h69fc3caa6bb155fa","symbolLocation":260,"imageIndex":0},{"imageOffset":5405316,"symbol":"std::sys::backtrace::__rust_begin_short_backtrace::h3711ebb41b529b4e","symbolLocation":224,"imageIndex":0},{"imageOffset":5407388,"symbol":"core::ops::function::FnOnce::call_once$u7b$$u7b$vtable.shim$u7d$$u7d$::h5b590e309155afbc","symbolLocation":92,"imageIndex":0},{"imageOffset":6756720,"symbol":"_RNvNvMs0_NtNtNtCsaLOjE9VYtxK_3std3sys6thread4unixNtB7_6Thread3new12thread_start","symbolLocation":408,"imageIndex":0},{"imageOffset":27736,"symbol":"_pthread_start","symbolLocation":136,"imageIndex":15},{"imageOffset":7196,"symbol":"thread_start","symbolLocation":8,"imageIndex":15}]},{"id":4631676,"name":"tokio-rt-worker","threadState":{"x":[{"value":260},{"value":0},{"value":256},{"value":0},{"value":0},{"value":160},{"value":0},{"value":0},{"value":6145353352},{"value":0},{"value":0},{"value":2},{"value":2},{"value":0},{"value":0},{"value":0},{"value":305},{"value":8510124096},{"value":0},{"value":44941300720},{"value":44941300784},{"value":6145356000},{"value":0},{"value":0},{"value":256},{"value":257},{"value":512},{"value":11400714819323198485},{"value":4349323544,"symbolLocation":0,"symbol":"parking_lot_core::parking_lot::HASHTABLE::h76c7a5179771e417"}],"flavor":"ARM_THREAD_STATE64","lr":{"value":6672736552},"cpsr":{"value":1610612736},"fp":{"value":6145353472},"sp":{"value":6145353328},"esr":{"value":1442840704,"description":"(Syscall)"},"pc":{"value":6672471308},"far":{"value":0}},"frames":[{"imageOffset":17676,"symbol":"__psynch_cvwait","symbolLocation":8,"imageIndex":14},{"imageOffset":28968,"symbol":"_pthread_cond_wait","symbolLocation":980,"imageIndex":15},{"imageOffset":5512976,"symbol":"parking_lot::condvar::Condvar::wait_until_internal::h7a8073d8c6fc70c3","symbolLocation":552,"imageIndex":0},{"imageOffset":5372784,"symbol":"tokio::runtime::scheduler::multi_thread::park::Inner::park_condvar::h7554bf8664fac1d7","symbolLocation":208,"imageIndex":0},{"imageOffset":5396536,"symbol":"tokio::runtime::scheduler::multi_thread::worker::Context::park_internal::h467e864812df67f8","symbolLocation":384,"imageIndex":0},{"imageOffset":5401184,"symbol":"tokio::runtime::scheduler::multi_thread::worker::Context::run::h3f04c0f91a4668a3","symbolLocation":3712,"imageIndex":0},{"imageOffset":5489348,"symbol":"tokio::runtime::context::scoped::Scoped$LT$T$GT$::set::h3b819941c9378206","symbolLocation":56,"imageIndex":0},{"imageOffset":5372108,"symbol":"tokio::runtime::context::runtime::enter_runtime::hed6f538e124ba00c","symbolLocation":492,"imageIndex":0},{"imageOffset":5390180,"symbol":"tokio::runtime::scheduler::multi_thread::worker::run::h750c64c6ac0235a6","symbolLocation":176,"imageIndex":0},{"imageOffset":5428896,"symbol":"_$LT$tokio..runtime..blocking..task..BlockingTask$LT$T$GT$$u20$as$u20$core..future..future..Future$GT$::poll::h28847489b1106f55","symbolLocation":108,"imageIndex":0},{"imageOffset":5449248,"symbol":"tokio::runtime::task::core::Core$LT$T$C$S$GT$::poll::h06297f738cd993bf","symbolLocation":164,"imageIndex":0},{"imageOffset":5366344,"symbol":"tokio::runtime::task::harness::Harness$LT$T$C$S$GT$::poll::h494a0f555e1b52e9","symbolLocation":168,"imageIndex":0},{"imageOffset":5443456,"symbol":"tokio::runtime::blocking::pool::Inner::run::h69fc3caa6bb155fa","symbolLocation":260,"imageIndex":0},{"imageOffset":5405316,"symbol":"std::sys::backtrace::__rust_begin_short_backtrace::h3711ebb41b529b4e","symbolLocation":224,"imageIndex":0},{"imageOffset":5407388,"symbol":"core::ops::function::FnOnce::call_once$u7b$$u7b$vtable.shim$u7d$$u7d$::h5b590e309155afbc","symbolLocation":92,"imageIndex":0},{"imageOffset":6756720,"symbol":"_RNvNvMs0_NtNtNtCsaLOjE9VYtxK_3std3sys6thread4unixNtB7_6Thread3new12thread_start","symbolLocation":408,"imageIndex":0},{"imageOffset":27736,"symbol":"_pthread_start","symbolLocation":136,"imageIndex":15},{"imageOffset":7196,"symbol":"thread_start","symbolLocation":8,"imageIndex":15}]},{"id":4631677,"name":"tokio-rt-worker","threadState":{"x":[{"value":260},{"value":0},{"value":256},{"value":0},{"value":0},{"value":160},{"value":0},{"value":0},{"value":6147499656},{"value":0},{"value":0},{"value":2},{"value":2},{"value":0},{"value":0},{"value":0},{"value":305},{"value":8510124096},{"value":0},{"value":44941301616},{"value":44941301680},{"value":6147502304},{"value":0},{"value":0},{"value":256},{"value":257},{"value":512},{"value":11400714819323198485},{"value":4349323544,"symbolLocation":0,"symbol":"parking_lot_core::parking_lot::HASHTABLE::h76c7a5179771e417"}],"flavor":"ARM_THREAD_STATE64","lr":{"value":6672736552},"cpsr":{"value":1610612736},"fp":{"value":6147499776},"sp":{"value":6147499632},"esr":{"value":1442840704,"description":"(Syscall)"},"pc":{"value":6672471308},"far":{"value":0}},"frames":[{"imageOffset":17676,"symbol":"__psynch_cvwait","symbolLocation":8,"imageIndex":14},{"imageOffset":28968,"symbol":"_pthread_cond_wait","symbolLocation":980,"imageIndex":15},{"imageOffset":5512976,"symbol":"parking_lot::condvar::Condvar::wait_until_internal::h7a8073d8c6fc70c3","symbolLocation":552,"imageIndex":0},{"imageOffset":5372784,"symbol":"tokio::runtime::scheduler::multi_thread::park::Inner::park_condvar::h7554bf8664fac1d7","symbolLocation":208,"imageIndex":0},{"imageOffset":5396536,"symbol":"tokio::runtime::scheduler::multi_thread::worker::Context::park_internal::h467e864812df67f8","symbolLocation":384,"imageIndex":0},{"imageOffset":5401184,"symbol":"tokio::runtime::scheduler::multi_thread::worker::Context::run::h3f04c0f91a4668a3","symbolLocation":3712,"imageIndex":0},{"imageOffset":5489348,"symbol":"tokio::runtime::context::scoped::Scoped$LT$T$GT$::set::h3b819941c9378206","symbolLocation":56,"imageIndex":0},{"imageOffset":5372108,"symbol":"tokio::runtime::context::runtime::enter_runtime::hed6f538e124ba00c","symbolLocation":492,"imageIndex":0},{"imageOffset":5390180,"symbol":"tokio::runtime::scheduler::multi_thread::worker::run::h750c64c6ac0235a6","symbolLocation":176,"imageIndex":0},{"imageOffset":5428896,"symbol":"_$LT$tokio..runtime..blocking..task..BlockingTask$LT$T$GT$$u20$as$u20$core..future..future..Future$GT$::poll::h28847489b1106f55","symbolLocation":108,"imageIndex":0},{"imageOffset":5449248,"symbol":"tokio::runtime::task::core::Core$LT$T$C$S$GT$::poll::h06297f738cd993bf","symbolLocation":164,"imageIndex":0},{"imageOffset":5366344,"symbol":"tokio::runtime::task::harness::Harness$LT$T$C$S$GT$::poll::h494a0f555e1b52e9","symbolLocation":168,"imageIndex":0},{"imageOffset":5443456,"symbol":"tokio::runtime::blocking::pool::Inner::run::h69fc3caa6bb155fa","symbolLocation":260,"imageIndex":0},{"imageOffset":5405316,"symbol":"std::sys::backtrace::__rust_begin_short_backtrace::h3711ebb41b529b4e","symbolLocation":224,"imageIndex":0},{"imageOffset":5407388,"symbol":"core::ops::function::FnOnce::call_once$u7b$$u7b$vtable.shim$u7d$$u7d$::h5b590e309155afbc","symbolLocation":92,"imageIndex":0},{"imageOffset":6756720,"symbol":"_RNvNvMs0_NtNtNtCsaLOjE9VYtxK_3std3sys6thread4unixNtB7_6Thread3new12thread_start","symbolLocation":408,"imageIndex":0},{"imageOffset":27736,"symbol":"_pthread_start","symbolLocation":136,"imageIndex":15},{"imageOffset":7196,"symbol":"thread_start","symbolLocation":8,"imageIndex":15}]},{"id":4631678,"name":"tokio-rt-worker","threadState":{"x":[{"value":260},{"value":0},{"value":0},{"value":0},{"value":0},{"value":160},{"value":0},{"value":0},{"value":6149645960},{"value":0},{"value":0},{"value":2},{"value":2},{"value":0},{"value":0},{"value":0},{"value":305},{"value":8510124096},{"value":0},{"value":44941302512},{"value":44941302576},{"value":6149648608},{"value":0},{"value":0},{"value":0},{"value":1},{"value":256},{"value":11400714819323198485},{"value":4349323544,"symbolLocation":0,"symbol":"parking_lot_core::parking_lot::HASHTABLE::h76c7a5179771e417"}],"flavor":"ARM_THREAD_STATE64","lr":{"value":6672736552},"cpsr":{"value":1610612736},"fp":{"value":6149646080},"sp":{"value":6149645936},"esr":{"value":1442840704,"description":"(Syscall)"},"pc":{"value":6672471308},"far":{"value":0}},"frames":[{"imageOffset":17676,"symbol":"__psynch_cvwait","symbolLocation":8,"imageIndex":14},{"imageOffset":28968,"symbol":"_pthread_cond_wait","symbolLocation":980,"imageIndex":15},{"imageOffset":5512976,"symbol":"parking_lot::condvar::Condvar::wait_until_internal::h7a8073d8c6fc70c3","symbolLocation":552,"imageIndex":0},{"imageOffset":5372784,"symbol":"tokio::runtime::scheduler::multi_thread::park::Inner::park_condvar::h7554bf8664fac1d7","symbolLocation":208,"imageIndex":0},{"imageOffset":5396536,"symbol":"tokio::runtime::scheduler::multi_thread::worker::Context::park_internal::h467e864812df67f8","symbolLocation":384,"imageIndex":0},{"imageOffset":5401184,"symbol":"tokio::runtime::scheduler::multi_thread::worker::Context::run::h3f04c0f91a4668a3","symbolLocation":3712,"imageIndex":0},{"imageOffset":5489348,"symbol":"tokio::runtime::context::scoped::Scoped$LT$T$GT$::set::h3b819941c9378206","symbolLocation":56,"imageIndex":0},{"imageOffset":5372108,"symbol":"tokio::runtime::context::runtime::enter_runtime::hed6f538e124ba00c","symbolLocation":492,"imageIndex":0},{"imageOffset":5390180,"symbol":"tokio::runtime::scheduler::multi_thread::worker::run::h750c64c6ac0235a6","symbolLocation":176,"imageIndex":0},{"imageOffset":5428896,"symbol":"_$LT$tokio..runtime..blocking..task..BlockingTask$LT$T$GT$$u20$as$u20$core..future..future..Future$GT$::poll::h28847489b1106f55","symbolLocation":108,"imageIndex":0},{"imageOffset":5449248,"symbol":"tokio::runtime::task::core::Core$LT$T$C$S$GT$::poll::h06297f738cd993bf","symbolLocation":164,"imageIndex":0},{"imageOffset":5366344,"symbol":"tokio::runtime::task::harness::Harness$LT$T$C$S$GT$::poll::h494a0f555e1b52e9","symbolLocation":168,"imageIndex":0},{"imageOffset":5443456,"symbol":"tokio::runtime::blocking::pool::Inner::run::h69fc3caa6bb155fa","symbolLocation":260,"imageIndex":0},{"imageOffset":5405316,"symbol":"std::sys::backtrace::__rust_begin_short_backtrace::h3711ebb41b529b4e","symbolLocation":224,"imageIndex":0},{"imageOffset":5407388,"symbol":"core::ops::function::FnOnce::call_once$u7b$$u7b$vtable.shim$u7d$$u7d$::h5b590e309155afbc","symbolLocation":92,"imageIndex":0},{"imageOffset":6756720,"symbol":"_RNvNvMs0_NtNtNtCsaLOjE9VYtxK_3std3sys6thread4unixNtB7_6Thread3new12thread_start","symbolLocation":408,"imageIndex":0},{"imageOffset":27736,"symbol":"_pthread_start","symbolLocation":136,"imageIndex":15},{"imageOffset":7196,"symbol":"thread_start","symbolLocation":8,"imageIndex":15}]},{"id":4631679,"name":"tokio-rt-worker","threadState":{"x":[{"value":260},{"value":0},{"value":1536},{"value":0},{"value":0},{"value":160},{"value":0},{"value":0},{"value":6151792264},{"value":0},{"value":0},{"value":2},{"value":2},{"value":0},{"value":0},{"value":0},{"value":305},{"value":8510124096},{"value":0},{"value":44941303408},{"value":44941303472},{"value":6151794912},{"value":0},{"value":0},{"value":1536},{"value":1537},{"value":1792},{"value":11400714819323198485},{"value":4349323544,"symbolLocation":0,"symbol":"parking_lot_core::parking_lot::HASHTABLE::h76c7a5179771e417"}],"flavor":"ARM_THREAD_STATE64","lr":{"value":6672736552},"cpsr":{"value":1610612736},"fp":{"value":6151792384},"sp":{"value":6151792240},"esr":{"value":1442840704,"description":"(Syscall)"},"pc":{"value":6672471308},"far":{"value":0}},"frames":[{"imageOffset":17676,"symbol":"__psynch_cvwait","symbolLocation":8,"imageIndex":14},{"imageOffset":28968,"symbol":"_pthread_cond_wait","symbolLocation":980,"imageIndex":15},{"imageOffset":5512976,"symbol":"parking_lot::condvar::Condvar::wait_until_internal::h7a8073d8c6fc70c3","symbolLocation":552,"imageIndex":0},{"imageOffset":5372784,"symbol":"tokio::runtime::scheduler::multi_thread::park::Inner::park_condvar::h7554bf8664fac1d7","symbolLocation":208,"imageIndex":0},{"imageOffset":5396536,"symbol":"tokio::runtime::scheduler::multi_thread::worker::Context::park_internal::h467e864812df67f8","symbolLocation":384,"imageIndex":0},{"imageOffset":5401184,"symbol":"tokio::runtime::scheduler::multi_thread::worker::Context::run::h3f04c0f91a4668a3","symbolLocation":3712,"imageIndex":0},{"imageOffset":5489348,"symbol":"tokio::runtime::context::scoped::Scoped$LT$T$GT$::set::h3b819941c9378206","symbolLocation":56,"imageIndex":0},{"imageOffset":5372108,"symbol":"tokio::runtime::context::runtime::enter_runtime::hed6f538e124ba00c","symbolLocation":492,"imageIndex":0},{"imageOffset":5390180,"symbol":"tokio::runtime::scheduler::multi_thread::worker::run::h750c64c6ac0235a6","symbolLocation":176,"imageIndex":0},{"imageOffset":5428896,"symbol":"_$LT$tokio..runtime..blocking..task..BlockingTask$LT$T$GT$$u20$as$u20$core..future..future..Future$GT$::poll::h28847489b1106f55","symbolLocation":108,"imageIndex":0},{"imageOffset":5449248,"symbol":"tokio::runtime::task::core::Core$LT$T$C$S$GT$::poll::h06297f738cd993bf","symbolLocation":164,"imageIndex":0},{"imageOffset":5366344,"symbol":"tokio::runtime::task::harness::Harness$LT$T$C$S$GT$::poll::h494a0f555e1b52e9","symbolLocation":168,"imageIndex":0},{"imageOffset":5443456,"symbol":"tokio::runtime::blocking::pool::Inner::run::h69fc3caa6bb155fa","symbolLocation":260,"imageIndex":0},{"imageOffset":5405316,"symbol":"std::sys::backtrace::__rust_begin_short_backtrace::h3711ebb41b529b4e","symbolLocation":224,"imageIndex":0},{"imageOffset":5407388,"symbol":"core::ops::function::FnOnce::call_once$u7b$$u7b$vtable.shim$u7d$$u7d$::h5b590e309155afbc","symbolLocation":92,"imageIndex":0},{"imageOffset":6756720,"symbol":"_RNvNvMs0_NtNtNtCsaLOjE9VYtxK_3std3sys6thread4unixNtB7_6Thread3new12thread_start","symbolLocation":408,"imageIndex":0},{"imageOffset":27736,"symbol":"_pthread_start","symbolLocation":136,"imageIndex":15},{"imageOffset":7196,"symbol":"thread_start","symbolLocation":8,"imageIndex":15}]},{"id":4631680,"name":"tokio-rt-worker","threadState":{"x":[{"value":260},{"value":0},{"value":0},{"value":0},{"value":0},{"value":160},{"value":0},{"value":0},{"value":6153938568},{"value":0},{"value":0},{"value":2},{"value":2},{"value":0},{"value":0},{"value":0},{"value":305},{"value":8510124096},{"value":0},{"value":44941304304},{"value":44941304368},{"value":6153941216},{"value":0},{"value":0},{"value":0},{"value":1},{"value":256},{"value":11400714819323198485},{"value":4349323544,"symbolLocation":0,"symbol":"parking_lot_core::parking_lot::HASHTABLE::h76c7a5179771e417"}],"flavor":"ARM_THREAD_STATE64","lr":{"value":6672736552},"cpsr":{"value":1610612736},"fp":{"value":6153938688},"sp":{"value":6153938544},"esr":{"value":1442840704,"description":"(Syscall)"},"pc":{"value":6672471308},"far":{"value":0}},"frames":[{"imageOffset":17676,"symbol":"__psynch_cvwait","symbolLocation":8,"imageIndex":14},{"imageOffset":28968,"symbol":"_pthread_cond_wait","symbolLocation":980,"imageIndex":15},{"imageOffset":5512976,"symbol":"parking_lot::condvar::Condvar::wait_until_internal::h7a8073d8c6fc70c3","symbolLocation":552,"imageIndex":0},{"imageOffset":5372784,"symbol":"tokio::runtime::scheduler::multi_thread::park::Inner::park_condvar::h7554bf8664fac1d7","symbolLocation":208,"imageIndex":0},{"imageOffset":5396536,"symbol":"tokio::runtime::scheduler::multi_thread::worker::Context::park_internal::h467e864812df67f8","symbolLocation":384,"imageIndex":0},{"imageOffset":5401184,"symbol":"tokio::runtime::scheduler::multi_thread::worker::Context::run::h3f04c0f91a4668a3","symbolLocation":3712,"imageIndex":0},{"imageOffset":5489348,"symbol":"tokio::runtime::context::scoped::Scoped$LT$T$GT$::set::h3b819941c9378206","symbolLocation":56,"imageIndex":0},{"imageOffset":5372108,"symbol":"tokio::runtime::context::runtime::enter_runtime::hed6f538e124ba00c","symbolLocation":492,"imageIndex":0},{"imageOffset":5390180,"symbol":"tokio::runtime::scheduler::multi_thread::worker::run::h750c64c6ac0235a6","symbolLocation":176,"imageIndex":0},{"imageOffset":5428896,"symbol":"_$LT$tokio..runtime..blocking..task..BlockingTask$LT$T$GT$$u20$as$u20$core..future..future..Future$GT$::poll::h28847489b1106f55","symbolLocation":108,"imageIndex":0},{"imageOffset":5449248,"symbol":"tokio::runtime::task::core::Core$LT$T$C$S$GT$::poll::h06297f738cd993bf","symbolLocation":164,"imageIndex":0},{"imageOffset":5366344,"symbol":"tokio::runtime::task::harness::Harness$LT$T$C$S$GT$::poll::h494a0f555e1b52e9","symbolLocation":168,"imageIndex":0},{"imageOffset":5443456,"symbol":"tokio::runtime::blocking::pool::Inner::run::h69fc3caa6bb155fa","symbolLocation":260,"imageIndex":0},{"imageOffset":5405316,"symbol":"std::sys::backtrace::__rust_begin_short_backtrace::h3711ebb41b529b4e","symbolLocation":224,"imageIndex":0},{"imageOffset":5407388,"symbol":"core::ops::function::FnOnce::call_once$u7b$$u7b$vtable.shim$u7d$$u7d$::h5b590e309155afbc","symbolLocation":92,"imageIndex":0},{"imageOffset":6756720,"symbol":"_RNvNvMs0_NtNtNtCsaLOjE9VYtxK_3std3sys6thread4unixNtB7_6Thread3new12thread_start","symbolLocation":408,"imageIndex":0},{"imageOffset":27736,"symbol":"_pthread_start","symbolLocation":136,"imageIndex":15},{"imageOffset":7196,"symbol":"thread_start","symbolLocation":8,"imageIndex":15}]},{"id":4631681,"name":"tokio-rt-worker","threadState":{"x":[{"value":260},{"value":0},{"value":256},{"value":0},{"value":0},{"value":160},{"value":0},{"value":0},{"value":6156084872},{"value":0},{"value":0},{"value":2},{"value":2},{"value":0},{"value":0},{"value":0},{"value":305},{"value":8510124096},{"value":0},{"value":44941305200},{"value":44941305264},{"value":6156087520},{"value":0},{"value":0},{"value":256},{"value":257},{"value":512},{"value":11400714819323198485},{"value":4349323544,"symbolLocation":0,"symbol":"parking_lot_core::parking_lot::HASHTABLE::h76c7a5179771e417"}],"flavor":"ARM_THREAD_STATE64","lr":{"value":6672736552},"cpsr":{"value":1610612736},"fp":{"value":6156084992},"sp":{"value":6156084848},"esr":{"value":1442840704,"description":"(Syscall)"},"pc":{"value":6672471308},"far":{"value":0}},"frames":[{"imageOffset":17676,"symbol":"__psynch_cvwait","symbolLocation":8,"imageIndex":14},{"imageOffset":28968,"symbol":"_pthread_cond_wait","symbolLocation":980,"imageIndex":15},{"imageOffset":5512976,"symbol":"parking_lot::condvar::Condvar::wait_until_internal::h7a8073d8c6fc70c3","symbolLocation":552,"imageIndex":0},{"imageOffset":5372784,"symbol":"tokio::runtime::scheduler::multi_thread::park::Inner::park_condvar::h7554bf8664fac1d7","symbolLocation":208,"imageIndex":0},{"imageOffset":5396536,"symbol":"tokio::runtime::scheduler::multi_thread::worker::Context::park_internal::h467e864812df67f8","symbolLocation":384,"imageIndex":0},{"imageOffset":5401184,"symbol":"tokio::runtime::scheduler::multi_thread::worker::Context::run::h3f04c0f91a4668a3","symbolLocation":3712,"imageIndex":0},{"imageOffset":5489348,"symbol":"tokio::runtime::context::scoped::Scoped$LT$T$GT$::set::h3b819941c9378206","symbolLocation":56,"imageIndex":0},{"imageOffset":5372108,"symbol":"tokio::runtime::context::runtime::enter_runtime::hed6f538e124ba00c","symbolLocation":492,"imageIndex":0},{"imageOffset":5390180,"symbol":"tokio::runtime::scheduler::multi_thread::worker::run::h750c64c6ac0235a6","symbolLocation":176,"imageIndex":0},{"imageOffset":5428896,"symbol":"_$LT$tokio..runtime..blocking..task..BlockingTask$LT$T$GT$$u20$as$u20$core..future..future..Future$GT$::poll::h28847489b1106f55","symbolLocation":108,"imageIndex":0},{"imageOffset":5449248,"symbol":"tokio::runtime::task::core::Core$LT$T$C$S$GT$::poll::h06297f738cd993bf","symbolLocation":164,"imageIndex":0},{"imageOffset":5366344,"symbol":"tokio::runtime::task::harness::Harness$LT$T$C$S$GT$::poll::h494a0f555e1b52e9","symbolLocation":168,"imageIndex":0},{"imageOffset":5443456,"symbol":"tokio::runtime::blocking::pool::Inner::run::h69fc3caa6bb155fa","symbolLocation":260,"imageIndex":0},{"imageOffset":5405316,"symbol":"std::sys::backtrace::__rust_begin_short_backtrace::h3711ebb41b529b4e","symbolLocation":224,"imageIndex":0},{"imageOffset":5407388,"symbol":"core::ops::function::FnOnce::call_once$u7b$$u7b$vtable.shim$u7d$$u7d$::h5b590e309155afbc","symbolLocation":92,"imageIndex":0},{"imageOffset":6756720,"symbol":"_RNvNvMs0_NtNtNtCsaLOjE9VYtxK_3std3sys6thread4unixNtB7_6Thread3new12thread_start","symbolLocation":408,"imageIndex":0},{"imageOffset":27736,"symbol":"_pthread_start","symbolLocation":136,"imageIndex":15},{"imageOffset":7196,"symbol":"thread_start","symbolLocation":8,"imageIndex":15}]},{"id":4631684,"frames":[],"threadState":{"x":[{"value":6156660736},{"value":56339},{"value":6156124160},{"value":0},{"value":409604},{"value":18446744073709551615},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0}],"flavor":"ARM_THREAD_STATE64","lr":{"value":0},"cpsr":{"value":0},"fp":{"value":0},"sp":{"value":6156660736},"esr":{"value":1442840704,"description":"(Syscall)"},"pc":{"value":6672714760},"far":{"value":0}}},{"id":4631685,"frames":[],"threadState":{"x":[{"value":6157234176},{"value":86043},{"value":6156697600},{"value":0},{"value":409604},{"value":18446744073709551615},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0}],"flavor":"ARM_THREAD_STATE64","lr":{"value":0},"cpsr":{"value":0},"fp":{"value":0},"sp":{"value":6157234176},"esr":{"value":1442840704,"description":"(Syscall)"},"pc":{"value":6672714760},"far":{"value":0}}},{"id":4631686,"frames":[],"threadState":{"x":[{"value":6157807616},{"value":51987},{"value":6157271040},{"value":0},{"value":409604},{"value":18446744073709551615},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0},{"value":0}],"flavor":"ARM_THREAD_STATE64","lr":{"value":0},"cpsr":{"value":0},"fp":{"value":0},"sp":{"value":6157807616},"esr":{"value":1442840704,"description":"(Syscall)"},"pc":{"value":6672714760},"far":{"value":0}}},{"id":4631697,"name":"Log work queue","threadState":{"x":[{"value":14},{"value":4693334498},{"value":0},{"value":6158375200},{"value":8441936896,"symbolLocation":0,"symbol":"_os_log_current_test_callback"},{"value":20},{"value":0},{"value":6158381280},{"value":0},{"value":0},{"value":0},{"value":0},{"value":6548},{"value":6548},{"value":8486814992,"symbolLocation":0,"symbol":"OBJC_CLASS_$_OS_os_log"},{"value":8486814992,"symbolLocation":0,"symbol":"OBJC_CLASS_$_OS_os_log"},{"value":18446744073709551580},{"value":8510128472},{"value":0},{"value":4747954304},{"value":4747954344},{"value":6158381056},{"value":0},{"value":0},{"value":4748006272},{"value":0},{"value":0},{"value":0},{"value":0}],"flavor":"ARM_THREAD_STATE64","lr":{"value":7399328140},"cpsr":{"value":2147483648},"fp":{"value":6158380880},"sp":{"value":6158380848},"esr":{"value":1442840704,"description":"(Syscall)"},"pc":{"value":6672456624},"far":{"value":0}},"frames":[{"imageOffset":2992,"symbol":"semaphore_wait_trap","symbolLocation":8,"imageIndex":14},{"imageOffset":18971020,"symbol":"IPC::StreamConnectionWorkQueue::startProcessingThread()::$_0::operator()()","symbolLocation":48,"imageIndex":8},{"imageOffset":2323588,"symbol":"WTF::Thread::entryPoint(WTF::Thread::NewThreadContext*)","symbolLocation":300,"imageIndex":9},{"imageOffset":24712,"symbol":"WTF::wtfThreadEntryPoint(void*)","symbolLocation":16,"imageIndex":9},{"imageOffset":27736,"symbol":"_pthread_start","symbolLocation":136,"imageIndex":15},{"imageOffset":7196,"symbol":"thread_start","symbolLocation":8,"imageIndex":15}]},{"id":4631746,"frames":[{"imageOffset":17676,"symbol":"__psynch_cvwait","symbolLocation":8,"imageIndex":14},{"imageOffset":28968,"symbol":"_pthread_cond_wait","symbolLocation":980,"imageIndex":15},{"imageOffset":5512976,"symbol":"parking_lot::condvar::Condvar::wait_until_internal::h7a8073d8c6fc70c3","symbolLocation":552,"imageIndex":0},{"imageOffset":5467288,"symbol":"tokio::runtime::park::Inner::park::h774be44801d85c39","symbolLocation":96,"imageIndex":0},{"imageOffset":5493796,"symbol":"tokio::runtime::scheduler::current_thread::Context::park_internal::ha3e118a43adf1c40","symbolLocation":160,"imageIndex":0},{"imageOffset":5494896,"symbol":"tokio::runtime::scheduler::current_thread::Context::park::h952215f60a571b6b","symbolLocation":572,"imageIndex":0},{"imageOffset":4370680,"symbol":"tokio::runtime::context::scoped::Scoped$LT$T$GT$::set::h9812401c9743de57","symbolLocation":316,"imageIndex":0},{"imageOffset":4397252,"symbol":"tokio::runtime::scheduler::current_thread::CoreGuard::block_on::ha938b86b18d880e1","symbolLocation":236,"imageIndex":0},{"imageOffset":4371636,"symbol":"tokio::runtime::context::runtime::enter_runtime::h3200400801bccd7f","symbolLocation":844,"imageIndex":0},{"imageOffset":4357388,"symbol":"tokio::runtime::runtime::Runtime::block_on::haf37f80d4a9b88a7","symbolLocation":176,"imageIndex":0},{"imageOffset":4496996,"symbol":"std::sys::backtrace::__rust_begin_short_backtrace::h10846183136523a1","symbolLocation":144,"imageIndex":0},{"imageOffset":4293356,"symbol":"core::ops::function::FnOnce::call_once$u7b$$u7b$vtable.shim$u7d$$u7d$::had4ee56b2cd17f44","symbolLocation":104,"imageIndex":0},{"imageOffset":6756720,"symbol":"_RNvNvMs0_NtNtNtCsaLOjE9VYtxK_3std3sys6thread4unixNtB7_6Thread3new12thread_start","symbolLocation":408,"imageIndex":0},{"imageOffset":27736,"symbol":"_pthread_start","symbolLocation":136,"imageIndex":15},{"imageOffset":7196,"symbol":"thread_start","symbolLocation":8,"imageIndex":15}],"threadState":{"x":[{"value":260},{"value":0},{"value":0},{"value":0},{"value":0},{"value":160},{"value":0},{"value":0},{"value":6160522984},{"value":0},{"value":0},{"value":2},{"value":2},{"value":0},{"value":0},{"value":0},{"value":305},{"value":8510124096},{"value":0},{"value":44941296240},{"value":44941296304},{"value":6160527584},{"value":0},{"value":0},{"value":0},{"value":1},{"value":256},{"value":11400714819323198485},{"value":4349323544,"symbolLocation":0,"symbol":"parking_lot_core::parking_lot::HASHTABLE::h76c7a5179771e417"}],"flavor":"ARM_THREAD_STATE64","lr":{"value":6672736552},"cpsr":{"value":1610612736},"fp":{"value":6160523104},"sp":{"value":6160522960},"esr":{"value":1442840704,"description":"(Syscall)"},"pc":{"value":6672471308},"far":{"value":0}}}],
  "usedImages" : [
  {
    "source" : "P",
    "arch" : "arm64",
    "base" : 4338548736,
    "CFBundleShortVersionString" : "0.1.0",
    "CFBundleIdentifier" : "com.kore.companion",
    "size" : 10240000,
    "uuid" : "0f7e9ca5-40a1-3f24-85f9-b7965689fb82",
    "path" : "\/Volumes\/VOLUME\/*\/kore-companion.app\/Contents\/MacOS\/kore-companion",
    "name" : "kore-companion",
    "CFBundleVersion" : "0.1.0"
  },
  {
    "source" : "P",
    "arch" : "arm64e",
    "base" : 4355276800,
    "size" : 49152,
    "uuid" : "ca58aa96-b997-3a6d-9132-19d49be4b3e9",
    "path" : "\/usr\/lib\/libobjc-trampolines.dylib",
    "name" : "libobjc-trampolines.dylib"
  },
  {
    "source" : "P",
    "arch" : "arm64e",
    "base" : 4695015424,
    "CFBundleShortVersionString" : "351.2",
    "CFBundleIdentifier" : "com.apple.AGXMetalG16G-B0",
    "size" : 8880128,
    "uuid" : "f763c26f-f4b8-3a78-858d-23e30c8e2485",
    "path" : "\/System\/Library\/Extensions\/AGXMetalG16G_B0.bundle\/Contents\/MacOS\/AGXMetalG16G_B0",
    "name" : "AGXMetalG16G_B0",
    "CFBundleVersion" : "351.2"
  },
  {
    "source" : "P",
    "arch" : "arm64e",
    "base" : 4687953920,
    "CFBundleShortVersionString" : "1.0",
    "CFBundleIdentifier" : "com.apple.AppleMetalOpenGLRenderer",
    "size" : 409600,
    "uuid" : "ed97217d-dbc3-3bd9-a531-e874ea072aa6",
    "path" : "\/System\/Library\/Extensions\/AppleMetalOpenGLRenderer.bundle\/Contents\/MacOS\/AppleMetalOpenGLRenderer",
    "name" : "AppleMetalOpenGLRenderer",
    "CFBundleVersion" : "1"
  },
  {
    "source" : "P",
    "arch" : "arm64e",
    "base" : 6668124160,
    "size" : 338764,
    "uuid" : "ff1d8ae4-abef-35f1-a30a-1183b9cb414f",
    "path" : "\/usr\/lib\/libobjc.A.dylib",
    "name" : "libobjc.A.dylib"
  },
  {
    "source" : "P",
    "arch" : "arm64e",
    "base" : 6744764416,
    "CFBundleShortVersionString" : "6.9",
    "CFBundleIdentifier" : "com.apple.AppKit",
    "size" : 24260512,
    "uuid" : "c92cc156-d767-322b-b79b-433f56e72561",
    "path" : "\/System\/Library\/Frameworks\/AppKit.framework\/Versions\/C\/AppKit",
    "name" : "AppKit",
    "CFBundleVersion" : "2685.60.104"
  },
  {
    "source" : "P",
    "arch" : "arm64e",
    "base" : 10738601984,
    "CFBundleShortVersionString" : "1.0",
    "CFBundleIdentifier" : "com.apple.TextInputUIMac",
    "size" : 73440,
    "uuid" : "9c3fefc1-96d6-3c7e-9d20-b9926f6d2cb0",
    "path" : "\/System\/Library\/PrivateFrameworks\/TextInputUIMacHelper.framework\/Versions\/A\/TextInputUIMacHelper",
    "name" : "TextInputUIMacHelper",
    "CFBundleVersion" : "1"
  },
  {
    "source" : "P",
    "arch" : "arm64e",
    "base" : 6670913536,
    "size" : 291392,
    "uuid" : "f071efe4-299f-3089-acc4-0025b8ffb52a",
    "path" : "\/usr\/lib\/system\/libdispatch.dylib",
    "name" : "libdispatch.dylib"
  },
  {
    "source" : "P",
    "arch" : "arm64e",
    "base" : 7380357120,
    "CFBundleShortVersionString" : "21624",
    "CFBundleIdentifier" : "com.apple.WebKit",
    "size" : 22973760,
    "uuid" : "49b21d99-8716-31b8-8686-71b287325f1d",
    "path" : "\/System\/Library\/Frameworks\/WebKit.framework\/Versions\/A\/WebKit",
    "name" : "WebKit",
    "CFBundleVersion" : "21624.2.5.11.8"
  },
  {
    "source" : "P",
    "arch" : "arm64e",
    "base" : 7241928704,
    "CFBundleShortVersionString" : "21624",
    "CFBundleIdentifier" : "com.apple.JavaScriptCore",
    "size" : 28271872,
    "uuid" : "1914f733-4af2-3ad7-9061-ca21ffc33841",
    "path" : "\/System\/Library\/Frameworks\/JavaScriptCore.framework\/Versions\/A\/JavaScriptCore",
    "name" : "JavaScriptCore",
    "CFBundleVersion" : "21624.2.5.11.8"
  },
  {
    "source" : "P",
    "arch" : "arm64e",
    "base" : 6672994304,
    "CFBundleShortVersionString" : "6.9",
    "CFBundleIdentifier" : "com.apple.CoreFoundation",
    "size" : 5628704,
    "uuid" : "4bbd0da8-c600-3f3a-a38b-6664652fa04a",
    "path" : "\/System\/Library\/Frameworks\/CoreFoundation.framework\/Versions\/A\/CoreFoundation",
    "name" : "CoreFoundation",
    "CFBundleVersion" : "5026.5.4.1.402"
  },
  {
    "source" : "P",
    "arch" : "arm64e",
    "base" : 6888628224,
    "CFBundleShortVersionString" : "2.1.1",
    "CFBundleIdentifier" : "com.apple.HIToolbox",
    "size" : 3125536,
    "uuid" : "8716490e-acc2-3688-8c2f-5ca42b4c9da9",
    "path" : "\/System\/Library\/Frameworks\/Carbon.framework\/Versions\/A\/Frameworks\/HIToolbox.framework\/Versions\/A\/HIToolbox",
    "name" : "HIToolbox"
  },
  {
    "source" : "P",
    "arch" : "arm64e",
    "base" : 6668681216,
    "size" : 680472,
    "uuid" : "f924bdd3-4365-3466-9580-8b1b3fa8f857",
    "path" : "\/usr\/lib\/dyld",
    "name" : "dyld"
  },
  {
    "size" : 0,
    "source" : "A",
    "base" : 0,
    "uuid" : "00000000-0000-0000-0000-000000000000"
  },
  {
    "source" : "P",
    "arch" : "arm64e",
    "base" : 6672453632,
    "size" : 250544,
    "uuid" : "fca53b98-3d6a-38b2-a0ec-df0f7e05f171",
    "path" : "\/usr\/lib\/system\/libsystem_kernel.dylib",
    "name" : "libsystem_kernel.dylib"
  },
  {
    "source" : "P",
    "arch" : "arm64e",
    "base" : 6672707584,
    "size" : 52028,
    "uuid" : "4f33683c-18c8-39a1-800b-2e3bd43bcc13",
    "path" : "\/usr\/lib\/system\/libsystem_pthread.dylib",
    "name" : "libsystem_pthread.dylib"
  },
  {
    "source" : "P",
    "arch" : "arm64e",
    "base" : 6781538304,
    "CFBundleShortVersionString" : "1.0",
    "CFBundleIdentifier" : "com.apple.TCC",
    "size" : 145304,
    "uuid" : "46ac4453-db23-3c07-a0eb-a68277a24098",
    "path" : "\/System\/Library\/PrivateFrameworks\/TCC.framework\/Versions\/A\/TCC",
    "name" : "TCC",
    "CFBundleVersion" : "1"
  },
  {
    "source" : "P",
    "arch" : "arm64e",
    "base" : 6669381632,
    "size" : 345440,
    "uuid" : "c40fcae8-7a17-3d82-87cb-3da4802adef1",
    "path" : "\/usr\/lib\/system\/libxpc.dylib",
    "name" : "libxpc.dylib"
  },
  {
    "source" : "P",
    "arch" : "arm64e",
    "base" : 6698606592,
    "CFBundleShortVersionString" : "6.9",
    "CFBundleIdentifier" : "com.apple.Foundation",
    "size" : 16655392,
    "uuid" : "0c8c2a94-a688-3529-b2bb-4640df195105",
    "path" : "\/System\/Library\/Frameworks\/Foundation.framework\/Versions\/C\/Foundation",
    "name" : "Foundation",
    "CFBundleVersion" : "5026.5.4.1.402"
  },
  {
    "source" : "P",
    "arch" : "arm64e",
    "base" : 6850711552,
    "CFBundleShortVersionString" : "1.8",
    "CFBundleIdentifier" : "com.apple.CoreVideo",
    "size" : 526432,
    "uuid" : "8a36cb95-d65e-3838-8837-22fd9a7e3d9c",
    "path" : "\/System\/Library\/Frameworks\/CoreVideo.framework\/Versions\/A\/CoreVideo",
    "name" : "CoreVideo",
    "CFBundleVersion" : "734.4"
  }
],
  "sharedCache" : {
  "base" : 6667550720,
  "size" : 5990973440,
  "uuid" : "157e6d2e-2e5c-39b1-8f2a-8866ee228bed"
},
  "vmSummary" : "ReadOnly portion of Libraries: Total=1.8G resident=0K(0%) swapped_out_or_unallocated=1.8G(100%)\nWritable regions: Total=4.4G written=673K(0%) resident=673K(0%) swapped_out=0K(0%) unallocated=4.4G(100%)\n\n                                VIRTUAL   REGION \nREGION TYPE                        SIZE    COUNT (non-coalesced) \n===========                     =======  ======= \nAccelerate framework               128K        1 \nActivity Tracing                   256K        1 \nAttributeGraph Data               1024K        1 \nColorSync                           32K        2 \nCoreAnimation                      512K       31 \nCoreGraphics                        64K        4 \nCoreUI image data                  144K        2 \nFoundation                          16K        1 \nJS VM Gigacage (reserved)          4.0G        1         reserved VM address space (unallocated)\nKernel Alloc Once                   32K        1 \nMALLOC                            57.4M       24 \nMALLOC guard page                 3328K        4 \nMemory Tag 22                     64.0M        1 \nSTACK GUARD                        416K       26 \nStack                             38.3M       27 \nStack Guard                       56.0M        1 \nVM_ALLOCATE                        496K       23 \nVM_ALLOCATE (reserved)            1536K       12         reserved VM address space (unallocated)\nWebKit Malloc                    192.1M        5 \nWebKit Malloc (reserved)          64.0M        1         reserved VM address space (unallocated)\n__AUTH                            5998K      634 \n__AUTH_CONST                      89.0M     1022 \n__CTF                               824        1 \n__DATA                            34.3M      975 \n__DATA_CONST                      34.9M     1030 \n__DATA_DIRTY                      8391K      880 \n__FONT_DATA                        2352        1 \n__GLSLBUILTINS                    5176K        1 \n__LINKEDIT                       579.2M        5 \n__OBJC_RO                         79.1M        1 \n__OBJC_RW                         2598K        1 \n__TEXT                             1.2G     1052 \n__TPRO_CONST                       128K        2 \nmapped file                      297.2M       44 \npage table in kernel               673K        1 \nshared memory                      864K       12 \n===========                     =======  ======= \nTOTAL                              6.8G     5831 \nTOTAL, minus reserved VM space     2.7G     5831 \n",
  "legacyInfo" : {
  "threadTriggered" : {
    "queue" : "com.apple.root.default-qos"
  }
},
  "logWritingSignature" : "0ab844cd143547aa72787c5fba42c0a238610f97",
  "bug_type" : "309",
  "roots_installed" : 0,
  "trmStatus" : 8192,
  "trialInfo" : {
  "rollouts" : [
    {
      "rolloutId" : "652eff3d1bce5442b8d753c9",
      "factorPackIds" : [

      ],
      "deploymentId" : 240000009
    },
    {
      "rolloutId" : "63508950b3714d3622fc77f7",
      "factorPackIds" : [
        "6526e111d0c9ce2f459b54a8"
      ],
      "deploymentId" : 240000015
    }
  ],
  "experiments" : [

  ]
}
}

Model: Mac16,10, BootROM 18000.121.3, proc 10:4:6:0 processors, 16 GB, SMC 
Graphics: Apple M4, Apple M4, Built-In
Display: 22B1W, 1920 x 1080 (1080p FHD - Full High Definition), Main, MirrorOff, Online
Memory Module: LPDDR5, Micron
AirPort: spairport_wireless_card_type_wifi (0x14E4, 0x4388), wl0: Feb  2 2026 19:39:59 version 23.50.20.0.41.51.208 FWID 01-010dcc74
IO80211_driverkit-1561.3 "IO80211_driverkit-1561.3" Apr 18 2026 17:42:26
AirPort: 
Bluetooth: Version (null), 0 services, 0 devices, 0 incoming serial ports
Network Service: Wi-Fi, AirPort, en1
Thunderbolt Bus: Mac mini, Apple Inc.
Thunderbolt Bus: Mac mini, Apple Inc.
Thunderbolt Bus: Mac mini, Apple Inc.
