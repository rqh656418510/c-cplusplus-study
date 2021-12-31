#include "file.h"

// 根据目录路径，从左到右依次判断目录是否存在，不存在则创建
// 注意：最后一个如果是目录的话，则必须加上 '\\' 或者 '/'
// 示例: /usr/local/scripts
int32_t createDirectory(const string &dirPath) {
    uint32_t dirPathLen = dirPath.length();
    if (dirPathLen > MAX_PATH_LEN) {
        return -1;
    }
    char tmpDirPath[MAX_PATH_LEN] = {0};
    for (uint32_t i = 0; i < dirPathLen; ++i) {
        tmpDirPath[i] = dirPath[i];
        if (tmpDirPath[i] == '\\' || tmpDirPath[i] == '/') {
            if (ACCESS(tmpDirPath, 0) != 0) {
                int32_t ret = MKDIR(tmpDirPath);
                if (ret != 0) {
                    return ret;
                }
            }
        }
    }
    return 0;
}
