# file-conversion
TLDR: learning how to work w/ images, sound files, videos!

## Motivation
I found myself bored during the winter break of my senior year and had been wanting to understand how different file formats work! My goal is to be able to have sufficient understanding of different file formats, e.g. PNG and JPEG, to convert between different formats.

## Tasks
1. To-do
    - need to create some kind of matrix and/or struct that can represent an image
    - research JPEG files
2. In progress
    - (most important for rn) learn about color types & color depths
    - need to add to int png_file::check_png_file(png_file*), so that it does more comprehensive checks
        - currently, just checking the PNG signature
    - need to refactor unsigned char* png_file::print_png_chunk_information(unsigned char*)
        - i don't like how it functions rn, might be the only way for rn?
    - as i update other functions, i have to keep changing void png_file::print_file_information(png_file*)
3. Complete
    - create png_file struct

## Sources
1. PNG (Third Edition) Documentation: https://www.w3.org/TR/png-3/