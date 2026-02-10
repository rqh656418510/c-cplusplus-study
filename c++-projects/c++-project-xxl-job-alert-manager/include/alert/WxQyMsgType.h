#pragma once

#include <string>

// 企业微信应用消息的类型
enum class WxQyMsgType : uint8_t {
    Text = 0,           // 文本消息
    Image,              // 图片消息
    Voice,              // 语言消息
    Video,              // 视频消息
    File,               // 文件消息
    TextCard,           // 文本卡片消息
    News,               // 图文消息
    MpNews,             // 图文消息
    Markdown,           // Markdown消息
    MiniProgramNotice,  // 小程序通知消息
    TemplateCard        // 模板卡片消息
};

// 将企业微信应用消息转换为字符串
const std::string toMsgTypeString(const WxQyMsgType& type) {
    switch (type) {
        case WxQyMsgType::Text:
            return "text";
        case WxQyMsgType::Image:
            return "image";
        case WxQyMsgType::Voice:
            return "voice";
        case WxQyMsgType::Video:
            return "video";
        case WxQyMsgType::File:
            return "file";
        case WxQyMsgType::TextCard:
            return "textcard";
        case WxQyMsgType::News:
            return "news";
        case WxQyMsgType::MpNews:
            return "mpnews";
        case WxQyMsgType::Markdown:
            return "markdown";
        case WxQyMsgType::MiniProgramNotice:
            return "miniprogram_notice";
        case WxQyMsgType::TemplateCard:
            return "template_card";
        default:
            return "unknown";
    }
}