/*
 *  程序名：crtsurfdata3.cpp  本程序用于生成全国气象站点观测的分钟数据。
 *  作者：Turing
*/

#include "_public.h"

// 全国气象站点参数结构体
struct st_stcode {
    char provname[31]; // 省份
    char obtid[11];    // 站号
    char obtname[31];  // 站名
    double lat;        // 纬度
    double lon;        // 精度
    double height;     // 海拔高度
};

// 存放全国气象站点参数的容器
vector<struct st_stcode> vstcode;

// 将全国气象站点参数文件中的数据加载到vstcode容器
bool LoadSTCode(const char *initfile);

// 全国气象站点分钟观测数据结构
struct st_surfdata {
    char obtid[11];      // 站点代码。
    char ddatetime[21];  // 数据时间：格式yyyymmddhh24miss
    int t;              // 气温：单位，0.1摄氏度。
    int p;              // 气压：0.1百帕。
    int u;              // 相对湿度，0-100之间的值。
    int wd;             // 风向，0-360之间的值。
    int wf;             // 风速：单位0.1m/s
    int r;              // 降雨量：0.1mm。
    int vis;            // 能见度：0.1米。
};

// 存放全国气象站点分钟观测数据的容器
vector<struct st_surfdata> vsurfdata;

// 模拟生成全国气象站点分钟观测数据，存放在vsurfdata容器中
void CrtSurfData();

// 日志文件
CLogFile logfile;

int main(int argc, char *argv[]) {
    if (argc != 4) {
        // 如果参数非法，给出帮助文档。
        printf("Using: ./crtsurfdata3 inifile outpath logfile\n");
        printf("Example: ./crtsurfdata3 ../ini/stcode.ini /tmp/surfdata /log/idc/crtsurfdata3.log\n\n");

        printf("inifile 全国气象站点参数文件名。\n");
        printf("outpath 全国气象站点数据文件存放的目录。\n");
        printf("logfile 本程序运行的日志文件名。\n\n");

        return -1;
    }

    if (logfile.Open(argv[3], "a+", false) == false) {
        printf("logfile.open(%s) failed.\n", argv[3]);
        return -1;
    }

    logfile.Write("crtsurfdata3 开始运行。\n");

    // 将全国气象站点参数文件中的数据加载到vstcode容器
    if (LoadSTCode(argv[1]) == false) {
        return -1;
    }

    // 模拟生成全国气象站点分钟观测数据，存放在vsurfdata容器中
    CrtSurfData();

    logfile.WriteEx("crtsurfdata3 结束运行。\n");

    return 0;
}

// 将全国气象站点参数文件中的数据加载到vstcode容器
bool LoadSTCode(const char *initfile) {
    CFile file;

    // 打开全国气象站点参数文件
    if (file.Open(initfile, "r") == false) {
        logfile.Write("file.Open(%s) failed.\n", initfile);
        return false;
    }

    CCmdStr cmdStr;
    char strBuffer[301];
    struct st_stcode stcode;

    while (true) {
        // 从全国气象站点参数文件中读取一行，如果已读取完，则跳出循环
        if (file.Fgets(strBuffer, 300, true) == false) {
            break;
        }

        // 将读取到一行内容拆分
        cmdStr.SplitToCmd(strBuffer, ",", true);

        // 忽略掉无效的行
        if (cmdStr.CmdCount() != 6) {
            continue;
        }

        // 将全国气象站点参数的每个数据项保存到站点参数结构体中
        memset(&stcode, 0, sizeof(struct st_stcode));
        cmdStr.GetValue(0, stcode.provname, 30); // 省份
        cmdStr.GetValue(1, stcode.obtid, 30);    // 站号
        cmdStr.GetValue(2, stcode.obtname, 30);  // 站名
        cmdStr.GetValue(3, &stcode.lat);         // 纬度
        cmdStr.GetValue(4, &stcode.lon);         // 经度
        cmdStr.GetValue(5, &stcode.height);      // 海拔高度

        // 将全国气象站点参数结构体放入站点参数容器中
        vstcode.push_back(stcode);
    }

    /*
    for (int i = 0; i < vstcode.size(); i++) {
        logfile.Write("provname=%s, obtid=%s, obtname=%s, lat=%.2f, lon=%.2f, height=%.2f\n",
                      vstcode[i].provname, vstcode[i].obtid, vstcode[i].obtname, vstcode[i].lat, vstcode[i].lon, vstcode[i].height);
    }
    */

    return true;
}

// 模拟生成全国气象站点分钟观测数据，存放在vsurfdata容器中
void CrtSurfData() {
    // 设置随机数种子
    srand(time(0));

    // 获取当前时间，当成观测时间
    char strddatetime[21];
    memset(strddatetime, 0, sizeof(strddatetime));
    LocalTime(strddatetime, "yyyymmddhh24miss");

    struct st_surfdata stsurfdata;

    // 遍历全国气象站点参数的vscode容器
    for (int i = 0; i < vstcode.size(); i++) {
        memset(&stsurfdata, 0, sizeof(struct st_surfdata));

        // 用随机数填充分钟观测数据的结构体
        strncpy(stsurfdata.obtid, vstcode[i].obtid, 10); // 站点代码。
        strncpy(stsurfdata.ddatetime, strddatetime, 14);  // 数据时间：格式yyyymmddhh24miss
        stsurfdata.t = rand() % 351;       // 气温：单位，0.1摄氏度
        stsurfdata.p = rand() % 265 + 10000; // 气压：0.1百帕
        stsurfdata.u = rand() % 100 + 1;     // 相对湿度，0-100之间的值。
        stsurfdata.wd = rand() % 360;      // 风向，0-360之间的值。
        stsurfdata.wf = rand() % 150;      // 风速：单位0.1m/s
        stsurfdata.r = rand() % 16;        // 降雨量：0.1mm
        stsurfdata.vis = rand() % 5001 + 100000;  // 能见度：0.1米

        // 将观测数据的结构体放入vsurfdata容器
        vsurfdata.push_back(stsurfdata);
    }

    /*
    for (int i = 0; i < vsurfdata.size(); i++) {
        logfile.Write("obtid=%s, ddatetime=%s, t=%d, p=%d, u=%d, wd=%d, wf=%d, r=%d, vis=%d\n",
                      vsurfdata[i].obtid, vsurfdata[i].ddatetime, vsurfdata[i].t, vsurfdata[i].p, vsurfdata[i].u,
                      vsurfdata[i].wd, vsurfdata[i].wf, vsurfdata[i].r, vsurfdata[i].vis);
    }
    */
}
