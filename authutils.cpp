#include "authutils.h"
#include <QCryptographicHash>
#include <QUuid>

namespace AuthUtils {

QString makeSalt(){
    return QUuid::createUuid().toString(QUuid::WithoutBraces);
}

QByteArray hmacSha256(const QByteArray &key, const QByteArray &data){
    QByteArray k = key;
    const int blockSize = 64; // block size for SHA-256
    if(k.size() > blockSize) k = QCryptographicHash::hash(k, QCryptographicHash::Sha256);
    if(k.size() < blockSize) k.append(QByteArray(blockSize - k.size(), 0x00));
    QByteArray o_key_pad(blockSize, 0x5c);
    QByteArray i_key_pad(blockSize, 0x36);
    for(int i=0;i<blockSize;i++){
        o_key_pad[i] = o_key_pad[i] ^ k[i];
        i_key_pad[i] = i_key_pad[i] ^ k[i];
    }
    QByteArray inner = QCryptographicHash::hash(i_key_pad + data, QCryptographicHash::Sha256);
    QByteArray result = QCryptographicHash::hash(o_key_pad + inner, QCryptographicHash::Sha256);
    return result;
}

QByteArray pbkdf2_hmac_sha256(const QByteArray &password, const QByteArray &salt, int iterations, int dkLen){
    int hashLen = 32;
    int l = (dkLen + hashLen - 1) / hashLen;
    QByteArray dk;
    for(int i=1;i<=l;i++){
        QByteArray intBlock;
        intBlock.append((char)((i >> 24) & 0xff));
        intBlock.append((char)((i >> 16) & 0xff));
        intBlock.append((char)((i >> 8) & 0xff));
        intBlock.append((char)(i & 0xff));
        QByteArray U = hmacSha256(password, salt + intBlock);
        QByteArray T = U;
        for(int j=1;j<iterations;j++){
            U = hmacSha256(password, U);
            for(int k=0;k<T.size();k++) T[k] = T[k] ^ U[k];
        }
        dk.append(T);
    }
    return dk.left(dkLen);
}

QString toHex(const QByteArray &ba){ return QString(ba.toHex()); }
QByteArray fromHex(const QString &hex){ return QByteArray::fromHex(hex.toUtf8()); }
QString sha256Simple(const QString &salt, const QString &password){
    QByteArray input = (salt + password).toUtf8();
    return QString(QCryptographicHash::hash(input, QCryptographicHash::Sha256).toHex());
}

}
