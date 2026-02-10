#pragma once

#include <memory>

#include "AlertChannel.h"
#include "AlertManager.h"
#include "CompositeAlert.h"
#include "EmailAlert.h"
#include "WxQyAlert.h"

// 复合告警
void compositeAlert() {
    std::shared_ptr<CompositeAlert> alert = std::make_shared<CompositeAlert>();
    alert->addChannel(std::make_shared<EmailAlert>());
    alert->addChannel(std::make_shared<WxQyAlert>());

    AlertManager manager(alert);
    manager.alert("XXL-JOB告警", "XXL-JOB已停止运行");
}