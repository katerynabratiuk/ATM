## Запуск проєкту

### Передумови

Потрібно мати встановлені:

- **Postgres**
- **Qt** (версія 6.9.3)
- **vcpkg**

Клонування репозиторію

   ```
   git clone https://github.com/katerynabratiuk/ATM
   ```

Встановити змінні оточення в .env за прикладом з .env.sample

### Postgres

В терміналі: 
```powershell
powershell -ExecutionPolicy Bypass -File .\init_db.ps1
```

### Visual Studio

1. View -> CMake Targets
2. Правою кнопкою на ATMSimulator (executable) -> Set as Startup Item
3. Зачекайте, поки згенерується cmake
4. Build -> Build all
5. Run в release mode або debug mode
