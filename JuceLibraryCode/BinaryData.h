/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   volumehigh_svg;
    const int            volumehigh_svgSize = 1294;

    extern const char*   start_svg;
    const int            start_svgSize = 533;

    extern const char*   pause_svg;
    const int            pause_svgSize = 527;

    extern const char*   NoVolume_svg;
    const int            NoVolume_svgSize = 836;

    extern const char*   GoForward_svg;
    const int            GoForward_svgSize = 618;

    extern const char*   GoBack_svg;
    const int            GoBack_svgSize = 615;

    extern const char*   End_svg;
    const int            End_svgSize = 529;

    extern const char*   circleplay_svg;
    const int            circleplay_svgSize = 749;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 8;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
