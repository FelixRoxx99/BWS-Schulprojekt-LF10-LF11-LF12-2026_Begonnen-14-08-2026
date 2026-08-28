#pragma once

#include <QString>
#include <QByteArray>

namespace AuthUtils {
    QString makeSalt();
    QByteArray pbkdf2_hmac_sha256(const QByteArray &password, const QByteArray &salt, int iterations, int dkLen);
    QString toHex(const QByteArray &ba);
    QByteArray fromHex(const QString &hex);
    QString sha256Simple(const QString &salt, const QString &password);
}
