# PDF Abyss

A free PDF library: upload, virus-scan, categorize and download PDFs.

- `frontend/` - Next.js 15 site (deployed to Cloudflare Pages)
- `backend/`  - FastAPI + Postgres + Redis/Celery + MinIO/S3 + ClamAV (run with Docker)

## Deploy the frontend on Cloudflare Pages

Create the Pages project from your GitHub repo with these settings:

| Setting | Value |
|---|---|
| Root directory | `frontend` |
| Build command | `npx @cloudflare/next-on-pages@1` |
| Build output directory | `.vercel/output/static` |
| Environment variable `NODE_VERSION` | `20` |
| Environment variable `NEXT_PUBLIC_API_URL` | your backend URL, e.g. `https://api.yourdomain.com` |

`frontend/wrangler.toml` already sets the required `nodejs_compat` flag.
If the dashboard ignores it, add it manually: **Settings > Functions > Compatibility flags** -> `nodejs_compat` (Production AND Preview), then redeploy.

Without that flag every page returns "Error - no nodejs_compat compatibility flag".

## Backend

Cloudflare Pages cannot run the backend (it needs Postgres, Redis, MinIO and ClamAV).
Run it on a VPS / Railway / Render / Fly.io:

```bash
cp .env.example .env     # set SECRET_KEY and admin password
docker compose up -d --build
```

Set `FRONTEND_URL` in `.env` to your Pages URL (comma-separated for several). `*.pages.dev` is already allowed by CORS.
Put the API behind HTTPS - a https site cannot call a http API (mixed content).
Note: download links are presigned S3 URLs, so `S3_ENDPOINT_URL` must be reachable from users' browsers in production (use real S3 / Cloudflare R2 / a public MinIO URL).

## Local development

```bash
cd frontend && cp .env.local.example .env.local && npm install && npm run dev
```
