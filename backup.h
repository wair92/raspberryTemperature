#ifndef BACKUP_H
#define BACKUP_H

#include <string>
class Backup{
public:
  void backupWorker();
private:
  void copy_backup_file(const std::string& backupDirectory,
      const std::string& fileForBackup);
};

#endif
