Get-Content ".env" | ForEach-Object {
    if ($_ -match "^\s*([^#][^=]*)\s*=\s*(.*)$") {
        $name = $matches[1]
        $value = $matches[2]
        $env:$name = $value
    }
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
psql -d $env:DB_NAME -f ".\db\schema.sql"

Write-Host "Done."
