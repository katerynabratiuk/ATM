function Set-EnvPersist {
    param(
        [string]$Name,
        [string]$Value
    )

    if ([string]::IsNullOrWhiteSpace($Value)) {
        return
    }

    $env:$Name = $Value

    [System.Environment]::SetEnvironmentVariable($Name, $Value, "User")
}

$envVars = @{}

Get-Content ".env" | ForEach-Object {
    if ($_ -match "^\s*([^#][^=]*)\s*=\s*(.*)$") {
        $name = $matches[1].Trim()
        $value = $matches[2].Trim()
        $envVars[$name] = $value
    }
}

if ($envVars.ContainsKey("QT_DIR")) {
    Set-EnvPersist -Name "QT_DIR" -Value $envVars["QT_DIR"]
}

if ($envVars.ContainsKey("VCPKG_ROOT")) {
    Set-EnvPersist -Name "VCPKG_ROOT" -Value $envVars["VCPKG_ROOT"]
}

if (-not $env:PGUSER)      { $env:PGUSER = $env:DB_USER }
if (-not $env:PGPASSWORD)  { $env:PGPASSWORD = $env:DB_PASSWORD }
if (-not $env:PGHOST)      { $env:PGHOST = $env:DB_HOST }
if (-not $env:PGPORT)      { $env:PGPORT = $env:DB_PORT }

$exists = psql -tAc "SELECT 1 FROM pg_database WHERE datname = '$($env:DB_NAME)';"

if (-not $exists) {
    Write-Host "Creating database $env:DB_NAME..."
    createdb $env:DB_NAME
} else {
    Write-Host "Database $env:DB_NAME already exists, skipping CREATE DATABASE"
}

Write-Host "Applying schema..."
psql -d $env:DB_NAME -f ".\schema.sql"

Write-Host "Done."
