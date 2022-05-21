#include "flink/flink.h"

//#include "stdafx.h"
#include "winnls.h"
#include "shobjidl.h"
#include "objbase.h"
#include "objidl.h"
#include "shlguid.h"

HRESULT CreateLinkW(LPWSTR lpszPathObj, LPWSTR lpszPathLink, LPWSTR lpszDesc, LPWSTR lpszIconPath, int iIcon)
{
    HRESULT hres;
    IShellLinkW* psl;

    // Get a pointer to the IShellLink interface. It is assumed that CoInitialize
    // has already been called.
    CoInitialize(NULL);
    hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLinkW, (LPVOID*)&psl);
    if (SUCCEEDED(hres))
    {
        IPersistFile* ppf;

        // Set the path to the shortcut target and add the description.
        psl->SetPath(lpszPathObj);
        psl->SetDescription(lpszDesc);
        psl->SetIconLocation(lpszIconPath, iIcon);

        // Query IShellLink for the IPersistFile interface, used for saving the
        // shortcut in persistent storage.
        hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf);

        if (SUCCEEDED(hres))
        {
            // WCHAR wsz[MAX_PATH];

            // Ensure that the string is Unicode.
            // MultiByteToWideChar(CP_ACP, 0, lpszPathLink, -1, wsz, MAX_PATH);

            // Add code here to check return value from MultiByteWideChar
            // for success.

            // Save the link by calling IPersistFile::Save.
            hres = ppf->Save(lpszPathLink, TRUE);
            ppf->Release();
        }
        psl->Release();
    }
    return hres;
}

extern "C" {
int flink_create(wchar_t *obj_path, wchar_t *link_path, wchar_t *desc, wchar_t *icon_path, int icon){
  HRESULT hres;

  hres = CreateLinkW( obj_path, link_path, desc, icon_path, icon );
  if( SUCCEEDED(hres) )
    return 0;
  return -1;
}

int flink_createA(char *obj_path, char *link_path, char *desc, char *icon_path, int icon){
  wchar_t obj_pathW[MAX_PATH], link_pathW[MAX_PATH], descW[MAX_PATH], icon_pathW[MAX_PATH];

  MultiByteToWideChar(CP_ACP, 0, obj_path, -1, obj_pathW, MAX_PATH);
  MultiByteToWideChar(CP_ACP, 0, link_path, -1, link_pathW, MAX_PATH);
  MultiByteToWideChar(CP_ACP, 0, desc, -1, descW, MAX_PATH);
  MultiByteToWideChar(CP_ACP, 0, icon_path, -1, icon_pathW, MAX_PATH);

  return flink_create( obj_pathW, link_pathW, descW, icon_pathW, icon );

}

}
