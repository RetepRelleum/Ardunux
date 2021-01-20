/*
 FS.cpp - file system wrapper 
 Copyright (c) 2015 Ivan Grokhotkov. All rights reserved.
 This file is part of the esp8266 core for Arduino environment.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "FS.h"

using namespace fs;

size_t File::write(uint8_t c)
{
    return fwrite(&c, sizeof(c), sizeof(c), fp);
}
time_t File::getLastWrite()
{
    time_t a;
    return a;
}
size_t File::write(const uint8_t *buf, size_t size)
{
    return fwrite(buf, sizeof(uint8_t), size, fp);
}
int File::available()
{
    size_t s = size();
    size_t p = position();
    return s - p;
}
int File::read()
{
    uint8_t result;
    if (fread(&result, 1, 1, fp) != 1)
    {
        return -1;
    }
    return result;
}

size_t File::read(uint8_t *buf, size_t size)
{
    return fread(buf, 1, size, fp);
}

int File::peek()
{
    fpos_t pos;
    fgetpos(fp, &pos);
    int r = read();
    fsetpos(fp, &pos);
    return r;
}

void File::flush()
{
    fflush(fp);
}

bool File::seek(uint32_t pos, SeekMode mode)
{
    return fseek(fp, pos, mode);
}

size_t File::position() const
{
    fpos_t pos;
    fgetpos(fp, &pos);
    return pos.__pos;
}

size_t File::size() const
{
    fpos_t position;
    fgetpos(fp, &position);
    fseek(fp, 0, SEEK_END);
    size_t ret = ftell(fp);
    fsetpos(fp, &position);
    return ret;
}

void File::close()
{
    if (dirp != nullptr)
    {
        closedir(dirp);
    }
    fclose(fp);
    fp = nullptr;
}

File::operator bool() const
{
    return !!fp;
}

const char *File::name() const
{
    return __name.c_str();
}

//to implement
bool File::isDirectory(void)
{
    struct stat st;
    stat(__name.c_str(), &st);

    return ((st.st_mode & S_IFDIR) != 0);
}

File File::openNextFile(const char *mode)
{
    struct dirent *dp;

    if (dirp == nullptr)
    {
        dirp = opendir(__name.c_str());
    }
    dp = readdir(dirp);
    if (dp == NULL)
    {
        File ret(nullptr);
        return ret;
    }
    if (String(dp->d_name)=="."|String(dp->d_name)=="..") {
        return openNextFile();
    }
    String na;
    na = __name + "/" + String(dp->d_name);
    File ret(::fopen(na.c_str(), mode));
    ret.__name = na;
    return ret;
}

void File::rewindDirectory(void)
{
    if (dirp != nullptr)
    {
        closedir(dirp);
    }
    dirp = nullptr;
}

File FS::open(const String &path, const char *mode)
{
    return open(path.c_str(), mode);
}

File FS::open(const char *path, const char *mode)
{
    FILE *ff = ::fopen(path, mode);
    File f = File(ff);
    f.__name = path;
    return f;
}

bool FS::exists(const char *path)
{
    if (FILE *file = fopen(path, "r"))
    {
        fclose(file);
        return true;
    }
    else
    {
        return false;
    }
}

bool FS::exists(const String &path)
{
    return exists(path.c_str());
}

bool FS::remove(const char *path)
{
    return (::remove(path) == 0);
}

bool FS::remove(const String &path)
{
    return remove(path.c_str());
}

bool FS::rename(const char *pathFrom, const char *pathTo)
{

    return (::rename(pathFrom, pathTo) == 0);
}

bool FS::rename(const String &pathFrom, const String &pathTo)
{
    return rename(pathFrom.c_str(), pathTo.c_str());
}

bool FS::mkdir(const char *path)
{
    return (::mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0);
}

bool FS::mkdir(const String &path)
{

    return mkdir(path.c_str());
}

bool FS::rmdir(const char *path)
{

    return (::rmdir(path) == 0);
}

bool FS::rmdir(const String &path)
{
    return rmdir(path.c_str());
}
