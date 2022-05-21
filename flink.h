#ifndef FLINK_H
#define FLINK_H

#include "windows.h"

HRESULT CreateLinkW(LPWSTR lpszPathObj, LPWSTR lpszPathLink, LPWSTR lpszDesc, LPWSTR lpszIconPath, int iIcon);

#ifdef __cplusplus
extern "C" {
#endif
int flink_create(wchar_t *obj_path, wchar_t *link_path, wchar_t *desc, wchar_t *icon_path, int icon);
int flink_createA(char *obj_path, char *link_path, char *desc, char *icon_path, int icon);

#ifdef __cplusplus
}
#endif


#endif
