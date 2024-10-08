/*
 *  程序名：crtsurfdata4.cpp  本程序用于生成全国气象站点观测的分钟数据。
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

// 观测数据的时间
char strddatetime[21];

// 模拟生成全国气象站点分钟观测数据，存放在vsurfdata容器中
void CrtSurfData();

// 将vsurfdata容器中的全国气象站点分钟观测数据写入文件
bool CrtSurfFile(const char *outpath, const char *datafmt);

// 日志文件
CLogFile logfile;

int main(int argc, char *argv[]) {
    if (argc != 5) {
        // 如果参数非法，给出帮助文档。
        printf("Using: ./crtsurfdata5 inifile outpath logfile datafmt\n");
        printf("Example: ./crtsurfdata5 ../ini/stcode.ini /tmp/idc/surfdata /var/log/idc/crtsurfdata5.log xml,json,csv\n\n");

        printf("inifile 全国气象站点参数文件名。\n");
        printf("outpath 全国气象站点数据文件存放的目录。\n");
        printf("logfile 本程序运行的日志文件名。\n");
        printf("datafmt 生成数据文件的格式，支持xml、json、csv三种格式，中间用逗号分割。\n\n");

        return -1;
    }

    if (logfile.Open(argv[3], "a+", false) == false) {
        printf("logfile.open(%s) failed.\n", argv[3]);
        return -1;
    }

    logfile.Write("crtsurfdata5 开始运行。\n");

    // 将全国气象站点参数文件中的数据加载到vstcode容器
    if (LoadSTCode(argv[1]) == false) {
        return -1;
    }

    // 模拟生成全国气象站点分钟观测数据，存放在vsurfdata容器中
    CrtSurfData();

    // 将vsurfdata容器中的全国气象站点分钟观测数据写入文件
    if (strstr(argv[4], "xml") != 0) CrtSurfFile(argv[2], "xml");
    if (strstr(argv[4], "json") != 0) CrtSurfFile(argv[2], "json");
    if (strstr(argv[4], "csv") != 0) CrtSurfFile(argv[2], "csv");

    logfile.WriteEx("crtsurfdata5 结束运行。\n");

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

// 将vsurfdata容器中的全国气象站点分钟观测数据写入文件
bool CrtSurfFile(const char *outpath, const char *datafmt) {
    CFile file;

    // 拼接生成数据的文件名，例如：/tmp/idc/surfdata/SURF_ZH_20210629092200_2254.csv
    char strFileName[301];
    sprintf(strFileName, "%s/SURF_ZH_%s_%d.%s", outpath, strddatetime, getpid(), datafmt);

    // 打开文件
    if (file.OpenForRename(strFileName, "w") == false) {
        logfile.Write("file.OpenForRename(%s) failed.\n", strFileName);
    }

    // 写入第一行的标题，只有 CSV 文件才需要有标题
    if (strcmp(datafmt, "csv") == 0) {
        file.Fprintf("站点代码,数据时间,气温,气压,相对湿度,风向,风速,降雨量,能见度\n");
    }

    // 写入根标签，只有 xml 文件才需要写
    if (strcmp(datafmt, "xml") == 0) {
        file.Fprintf("<data>\n");
    }

    // 写入根节点，只有 json 文件才需要
    if (strcmp(datafmt, "json") == 0) {
        file.Fprintf("{\"data\":[\n");
    }

    // 遍历存放分钟观测数据的vsurfdata容器
    for (int i = 0; i < vsurfdata.size(); i++) {
        // csv 文件写入一条记录
        if (strcmp(datafmt, "csv") == 0) {
            file.Fprintf("%s,%s,%.1f,%.1f,%d,%d,%.1f,%.1f,%.1f\n", \
            vsurfdata[i].obtid, vsurfdata[i].ddatetime, vsurfdata[i].t / 10.0, vsurfdata[i].p / 10.0, \
            vsurfdata[i].u, vsurfdata[i].wd, vsurfdata[i].wf / 10.0, vsurfdata[i].r / 10.0, vsurfdata[i].vis / 10.0);
        }

        // xml 文件写入一条记录
        if (strcmp(datafmt, "xml") == 0) {
            file.Fprintf("<obtid>%s</obtid><ddatetime>%s</ddatetime><t>%.1f</t><p>%.1f</p>" \
            "<u>%d</u><wd>%d</wd><wf>%.1f</wf><r>%.1f</r><vis>%.1f</vis><endl/>\n", \
            vsurfdata[i].obtid, vsurfdata[i].ddatetime, vsurfdata[i].t / 10.0, vsurfdata[i].p / 10.0, \
            vsurfdata[i].u, vsurfdata[i].wd, vsurfdata[i].wf / 10.0, vsurfdata[i].r / 10.0, vsurfdata[i].vis / 10.0);
        }

        // json 文件写入一条记录
        if (strcmp(datafmt, "json") == 0) {
            file.Fprintf("{\"obtid\":\"%s\",\"ddatetime\":\"%s\",\"t\":\"%.1f\",\"p\":\"%.1f\"," \
            "\"u\":\"%d\",\"wd\":\"%d\",\"wf\":\"%.1f\",\"r\":\"%.1f\",\"vis\":\"%.1f\"}", \
            vsurfdata[i].obtid, vsurfdata[i].ddatetime, vsurfdata[i].t / 10.0, vsurfdata[i].p / 10.0, \
            vsurfdata[i].u, vsurfdata[i].wd, vsurfdata[i].wf / 10.0, vsurfdata[i].r / 10.0, vsurfdata[i].vis / 10.0);
            if (i < vsurfdata.size() - 1) {
                file.Fprintf(",\n");
            } else {
                file.Fprintf("\n");
            }
        }

    }

    // 写入根标签，只有 xml 文件才需要写
    if (strcmp(datafmt, "xml") == 0) {
        file.Fprintf("</data>\n");
    }

    // 写入根节点，只有 json 文件才需要写
    if (strcmp(datafmt, "json") == 0) {
        file.Fprintf("]}\n");
    }

    // 关闭文件
    file.CloseAndRename();

    logfile.Write("生成数据文件 %s 成功，数据时间为 %s，记录数为 %d。\n", strFileName, strddatetime, vsurfdata.size());

    return true;
}
