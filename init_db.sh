set -euo pipefail

cd "$(dirname "$0")/.."

if [ -f ".env" ]; then
  set -a
  source ".env"
  set +a
else
  echo ".env file not found in $(pwd)"
  exit 1
fi

: "${PGUSER:=${DB_USER:-}}"
: "${PGPASSWORD:=${DB_PASSWORD:-}}"
: "${PGHOST:=${DB_HOST:-}}"
: "${PGPORT:=${DB_PORT:-}}"

export PGUSER PGPASSWORD PGHOST PGPORT

if [ -z "${DB_NAME:-}" ]; then
  echo "DB_NAME is not set in .env"
  exit 1
fi

exists=$(psql -tAc "SELECT 1 FROM pg_database WHERE datname = '${DB_NAME}';" || true)

if [ -z "$exists" ]; then
  echo "Creating database ${DB_NAME}..."
  createdb "${DB_NAME}"
else
  echo "Database ${DB_NAME} already exists, skipping CREATE DATABASE"
fi

echo "Applying schema..."
psql -d "${DB_NAME}" -f "./schema.sql"

echo "Done."