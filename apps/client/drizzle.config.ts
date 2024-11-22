import { defineConfig } from "drizzle-kit";

export default defineConfig({
  dialect: "postgresql",
  casing: 'snake_case',
  dbCredentials: {
    url: process.env.DATABASE_URL as string
  },
  // dbCredentials: ,
  schema: "./server/db/schema.ts",
});
