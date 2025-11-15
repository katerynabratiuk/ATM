## Вимоги:
1. Postgres
2. Qt 6.9.3
3. vcpkg
---
## Запус проєкту:

### База даних
1. Встановіть змінні оточення (`\.env`)
2. В powershell:   
```powershell
powershell -ExecutionPolicy Bypass -File .\init_db.ps1
```

### Відкрити в VS
1. Відкрийте Visual Studio
2. File → Open → Folder
3. Відкрийте кореневу директорію (в якій знаходиться CMakeLists.txt)
4. View -> CMake Targets
5. Правою кнопкою на ATMSimulator (executable) -> Set as Startup Item
6. Build -> Build all
7. RunDebug → Start Debugging (або F5)
або Debug → Start Without Debugging (Ctrl + F)