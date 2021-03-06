/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "SkDebugCanvas.h"
#include "SkNullCanvas.h"
#include "SkPicture.h"
#include "SkStream.h"

#include <iostream>

#ifdef SK_BUILD_FOR_WIN
#include <fcntl.h>
#include <io.h>
#endif

/*
If you execute skp_parser with one argument, it spits out a json representation
of the skp, but that's incomplete since it's missing many binary blobs (these
could represent images or typefaces or just anything that doesn't currently
have a json representation).  Each unique blob is labeled with a string in the
form "data/%d".  So for example:

    tools/git-sync-deps
    bin/gn gen out/debug
    ninja -C out/debug dm skp_parser
    out/debug/dm -m grayscale -w /tmp/dm --config skp
    out/debug/skp_parser /tmp/dm/skp/gm/grayscalejpg.skp | less
    out/debug/skp_parser /tmp/dm/skp/gm/grayscalejpg.skp | grep data
    out/debug/skp_parser /tmp/dm/skp/gm/grayscalejpg.skp data/0 | file -
    out/debug/skp_parser /tmp/dm/skp/gm/grayscalejpg.skp data/0 > /tmp/data0.png

"data/0" is an image that the SKP serializer has encoded as PNG.
*/
int main(int argc, char** argv) {
    if (argc < 2) {
        SkDebugf("Usage:\n  %s SKP_FILE [DATA_URL]\n", argv[0]);
        return 1;
    }
    SkFILEStream input(argv[1]);
    if (!input.isValid()) {
        SkDebugf("Bad file: '%s'\n", argv[1]);
        return 2;
    }
    sk_sp<SkPicture> pic = SkPicture::MakeFromStream(&input);
    if (!pic) {
        SkDebugf("Bad skp: '%s'\n", argv[1]);
        return 3;
    }
    SkISize size = pic->cullRect().roundOut().size();
    SkDebugCanvas debugCanvas(size.width(), size.height());
    pic->playback(&debugCanvas);
    std::unique_ptr<SkCanvas> nullCanvas = SkMakeNullCanvas();
    UrlDataManager dataManager(SkString("data"));
    Json::Value json = debugCanvas.toJSON(
            dataManager, debugCanvas.getSize(), nullCanvas.get());
    if (argc > 2) {
        if (UrlDataManager::UrlData* data =
            dataManager.getDataFromUrl(SkString(argv[2]))) {
            SkData* skdata = data->fData.get();
            SkASSERT(skdata);
            #ifdef SK_BUILD_FOR_WIN
            fflush(stdout);
            (void)_setmode(_fileno(stdout), _O_BINARY);
            #endif
            fwrite(skdata->data(), skdata->size(), 1, stdout);
        } else {
            SkDebugf("Bad data url.\n");
            return 4;
        }
    } else {
        Json::StyledStreamWriter("  ").write(std::cout, json);
    }
    return 0;
}
