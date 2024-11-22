import { drizzle } from 'drizzle-orm/node-postgres'
import * as schema from './schema'
import { Pool } from 'pg'

export const db = drizzle({ 
  connection: {
    connectionString: process.env.DATABASE_URL as string,
  },
  schema,
  casing: 'snake_case'
})