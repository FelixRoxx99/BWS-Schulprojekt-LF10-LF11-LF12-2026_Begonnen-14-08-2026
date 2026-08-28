q.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx_geraete_seriennummer ON geraete(seriennummer)");

    q.exec("CREATE TABLE IF NOT EXISTS ausleihe ("
           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
           "geraet_id INTEGER REFERENCES geraete(id),"
           "benutzer_id INTEGER REFERENCES benutzer(id),"
           "ausleihdatum TEXT,"
           "rueckgabedatum TEXT)");

    // ensure an admin user exists for testing. If users exist with plaintext passwords, migrate to hashed + salt.
    // Insert default entries only if username not exists.
    auto ensureUser = [&](const QString &username, const QString &plainPassword, const QString &role){
        QSqlQuery q2(db);
        q2.prepare("SELECT id, passwort, salt FROM benutzer WHERE benutzername=:u");
        q2.bindValue(":u", username);
        if(q2.exec() && q2.next()){
            // user exists -> ensure password is hashed (if not already)
            QString stored = q2.value(1).toString();
            QString salt = q2.value(2).toString();
            QRegularExpression re("^[0-9a-fA-F]{64}$");
            if(!re.match(stored).hasMatch()){
                // treat stored as plaintext, generate salt and hash
                QString s = makeSalt();
                QString hashed = hashPassword(s, stored);
                QSqlQuery u(db);
                u.prepare("UPDATE benutzer SET passwort=:p, salt=:s WHERE id=:id");
                u.bindValue(":p", hashed);
                u.bindValue(":s", s);
                u.bindValue(":id", q2.value(0).toInt());
                u.exec();
            }
        } else {
            // create user
            QString s = makeSalt();
            QString hashed = hashPassword(s, plainPassword);
            QSqlQuery ins(db);
            ins.prepare("INSERT INTO benutzer (benutzername, passwort, rolle, salt, kdf, iter) VALUES (:u,:p,:r,:s,:k,:i)");
            ins.bindValue(":u", username);
            ins.bindValue(":p", hashed);
            ins.bindValue(":r", role);
            ins.bindValue(":s", s);
            ins.bindValue(":k", "pbkdf2");
            ins.bindValue(":i", 100000);
            ins.exec();
        }
    };

    ensureUser("admin", "admin", "admin");
    ensureUser("user", "user", "user");

    // Show login dialog
    LoginDialog login;
    // center and activate the dialog so it appears in front of all windows
    QScreen *screen = QGuiApplication::primaryScreen();
    if(screen){
        QRect sg = screen->availableGeometry();
        login.adjustSize();
        QPoint center = sg.center() - QPoint(login.width()/2, login.height()/2);
        login.move(center);
    }
    login.setModal(true);
    login.setWindowModality(Qt::ApplicationModal);
    login.raise();
    login.activateWindow();

    if(login.exec() != QDialog::Accepted){
        return 0;
    }

    FrmMain w;
    w.setCurrentUser(login.userId(), login.role());
    w.show();
    return a.exec();
}
