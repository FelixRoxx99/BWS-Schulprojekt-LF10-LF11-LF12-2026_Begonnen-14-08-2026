#ifndef AUTHUTILS_H
#define AUTHUTILS_H

#include <QString>
#include <QByteArray>
#include <QSqlDatabase>

namespace AuthUtils {
    QString makeSalt();
    QByteArray hmacSha256(const QByteArray &key, const QByteArray &data);
    QByteArray pbkdf2_hmac_sha256(const QByteArray &password, const QByteArray &salt, int iterations, int dkLen);
    QString toHex(const QByteArray &ba);
    QByteArray fromHex(const QString &hex);
    QString sha256Simple(const QString &salt, const QString &password);
}

#endif // AUTHUTILS_H
