#include "audioplayer.h"

AudioPlayer* AudioPlayer::m_pInstance = NULL;

AudioPlayer* AudioPlayer::Instance() {
    if (!m_pInstance) {
        m_pInstance = new AudioPlayer;
    }

    return m_pInstance;
}

AudioPlayer::AudioPlayer(QObject *parent) : QObject(parent) {
    this->loadAudioList();
}

void AudioPlayer::loadAudioList() {
    QStringList filter;
    filter << "*.wav";

    QDir myDir(QDir::currentPath() + "/sounds");
    fileList = myDir.entryList(filter, QDir::Files, QDir::Name);
}

QStringList AudioPlayer::getAudioList() {
    return fileList;
}

void AudioPlayer::play(const QString& fileName) {
    if(!fileName.isEmpty() && fileList.contains(fileName)) {
        QSound::play(QDir::currentPath() + "/sounds/" + fileName);
    }
}
