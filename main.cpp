#include <iostream>
#include <Windows.h>

// Link required library
#pragma comment(lib, "urlmon.lib")

bool download(std::wstring_view url, std::wstring_view dest)
{
    const HRESULT res = URLDownloadToFileW(nullptr, url.data(), dest.data(), 0, nullptr);
    return SUCCEEDED(res);
}

int wmain(int argc, wchar_t **argv)
{
    const std::wstring url = L"https://zoom.us/client/latest/ZoomInstaller.exe";
    const std::wstring destination = L"C:/Users/Refraction/Downloads/zoom_installer.exe";

    if (!download(url, destination)) std::cout << "File was not loaded" << std::endl;
    else std::cout << "File was successfully downloaded" << std::endl;
}
