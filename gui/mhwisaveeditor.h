#ifndef MHWISAVEEDITOR_H
#define MHWISAVEEDITOR_H

#include <QMainWindow>
#include <QSignalMapper>

#include "../types/mhw_save.h"

#include "inventory/inventoryeditor.h"
#include "limitedunlocks.h"
#include "generalinfo.h"

constexpr const char* ALL_SAVE = "All Files (*)";
constexpr const char* ENCRYPTED_SAVE = "Encrypted Save (*.raw)";
constexpr const char* UNENCRYPTED_SAVE = "Unencrypted Save(*.bin)";

struct editor_tab {
  SaveLoader* widget;
  SaveLoader** binding;
  QString name;
};

QT_BEGIN_NAMESPACE
namespace Ui { class MHWISaveEditor; }
QT_END_NAMESPACE

class MHWISaveEditor : public QMainWindow
{
  Q_OBJECT

public slots:
  void Open();
  void OpenSAVEDATA1000();
  void Save();
  void Slot(int slot);
  void SwitchSlot(int slot);
  void CloneSlot(int slot);
  void OpenLocation(const QString& location);
  void Backup();
  void Restore();
  void Dump(int number);
  void EditorTabChange(int editorIndex);

public:
  MHWISaveEditor(QWidget* parent = nullptr);
  ~MHWISaveEditor();

  void closeEvent(QCloseEvent* event);

private:
  void SaveFile(const QString& path, mhw_save_raw** save, bool encrypt = true, bool validate = false);
  void LoadFile(const QString& path, mhw_save_raw** save);

  void LoadSaveSlot();

  Ui::MHWISaveEditor* ui;
  mhw_save_raw* mhwRaw = nullptr;
  int saveslot = 0;

  InventoryEditor* inventoryEditor = nullptr;
  LimitedUnlocks* limitedUnlocks = nullptr;
  GeneralInfo* generalInfo = nullptr;
  QList<SaveLoader*> editors;

  QSignalMapper* slotSignalMapper;
  QSignalMapper* switchSignalMapper;
  QSignalMapper* cloneSignalMapper;
  QSignalMapper* openSignalMapper;
  QSignalMapper* dumpSignalMapper;

  QList<QAction*> slotActions;
  QList<QAction*> switchActions;
  QList<QAction*> cloneActions;
};
#endif // MHWISAVEEDITOR_H
