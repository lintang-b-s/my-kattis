## Prerequisites

- Node.js 20+
- Python 3 with `autokattis` installed (`pip install autokattis`)

## Setup

1. Install dependencies:

   ```bash
   cd web
   npm install
   ```

2. (Optional) Configure your Open Kattis credentials in `web/.env.local` (see `.env.example`):

   ```env
   KATTIS_USERNAME=your_username
   KATTIS_PASSWORD=your_password
   ```

3. Sync your solved problems via `autokattis` (or click **Sync** in the web UI):

   ```bash
   npm run sync
   ```

4. Start the development server:
   ```bash
   npm run dev
   ```
   Open [http://localhost:3000](http://localhost:3000).

## Tests

```bash
npm test      # TypeScript unit tests (Vitest)
npm run test:py  # Python unit tests (unittest)
```
