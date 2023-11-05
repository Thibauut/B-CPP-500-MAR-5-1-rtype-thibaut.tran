/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Compress.hpp
*/

#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <zlib.h>

class Compressor {

    public:
        Compressor() {};
        ~Compressor() {};

        std::string compress(const std::string& input) {
            z_stream zs;
            memset(&zs, 0, sizeof(zs));
            if (deflateInit(&zs, Z_BEST_COMPRESSION) != Z_OK)
                return "";
            zs.next_in = (Bytef*)input.data();
            zs.avail_in = input.size();
            int ret;
            char buffer[32768];
            std::string compressed;
            do {
                zs.next_out = (Bytef*)buffer;
                zs.avail_out = sizeof(buffer);
                ret = deflate(&zs, Z_FINISH);
                if (compressed.size() < zs.total_out)
                    compressed.append(buffer, zs.total_out - compressed.size());
            } while (ret == Z_OK);
            deflateEnd(&zs);
            return compressed;
        }

        std::string decompress(const std::string& input) {
            z_stream zs;
            memset(&zs, 0, sizeof(zs));
            if (inflateInit(&zs) != Z_OK)
                return "";
            zs.next_in = (Bytef*)input.data();
            zs.avail_in = input.size();
            int ret;
            char buffer[32768];
            std::string decompressed;
            do {
                zs.next_out = (Bytef*)buffer;
                zs.avail_out = sizeof(buffer);

                ret = inflate(&zs, 0);

                if (decompressed.size() < zs.total_out) {
                    decompressed.append(buffer, zs.total_out - decompressed.size());
                }
            } while (ret == Z_OK);
            inflateEnd(&zs);
            return decompressed;
        }

};