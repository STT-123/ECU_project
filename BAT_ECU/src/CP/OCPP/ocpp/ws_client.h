#ifndef WS_CLIENT_H
#define WS_CLIENT_H
void *websocket_client_thread(void *arg);

// 外部请求 WebSocket 可写
void websocket_request_write(void);
#endif