//
// WorldMap.cpp
// Author: Samuel Vargas 
// Date: 09/14/2019
//

#include "worldmap.h"

WorldMap::WorldMap() {
    /*
     * Ultimately we need to send:
     *      1) A list of triangles
     *      2) What color those triangles should be
     *
     * The GPU will convert this to a rasterized image for us, and then
     * we can forward this image to imgui for rendering in a preview bo.
     */

    /*
     * Geometry:
     *  3 Rectangular Prisms for each thing on screen
     *  3 Letters + reusable numbers for axes / obj ids
     *  8 rectunaglr prisms for the bounding box
     *
     *
     *  Create:
     *      Some kind of builder pattern api for making a buffer of
     *      prism + solid color data
     *
     *      add support for adding geometry in that
     */
}