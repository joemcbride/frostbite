#include "dataconverterservice.h"

DataConverterService* DataConverterService::m_pInstance = NULL;

DataConverterService* DataConverterService::Instance() {
    if (!m_pInstance) {
        m_pInstance = new DataConverterService;
    }

    return m_pInstance;
}

DataConverterService::DataConverterService(QObject *parent) : QObject(parent) {
    this->populateExpStates();
}

void DataConverterService::populateExpStates() {
    mindStates << "clear" << "dabbling" << "perusing" << "learning" << "thoughtful"
        << "thinking" << "considering" << "pondering" << "ruminating" << "concentrating"
        << "attentive" << "deliberative" << "interested" << "examining" << "understanding" << "absorbing"
        << "intrigued" << "scrutinizing" << "analyzing" << "studious" << "focused" << "very focused"
        << "engaged" << "very engaged" << "cogitating" << "fascinated" << "captivated" << "engrossed" << "riveted"
        << "very riveted" << "rapt" << "very rapt" << "enthralled" << "nearly locked" << "mind lock";
}

int DataConverterService::expStateToNumeric(QString state) {
    return mindStates.indexOf(state);
}

int DataConverterService::expBriefToNumeric(QString state) {
    QRegExp rx("(\\d+)");
    rx.indexIn(state, 0);
    return rx.cap(1).toInt();
}

QString DataConverterService::expNumericToState(int index) {
    return mindStates.at(index);
}

QString DataConverterService::msToMMSS(int ms) {
    int ss = ms / 1000;
    int mm = ss / 60;
        ss = ss % 60;

    return QString().sprintf("%02d:%02d", mm, ss);
}