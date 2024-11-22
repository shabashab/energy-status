import { pgTable, uuid, real, timestamp, boolean } from 'drizzle-orm/pg-core'

export const updates = pgTable('updates', {
  id: uuid().defaultRandom().primaryKey(),

  temperature: real().notNull(),
  humidity: real().notNull(),

  power1: boolean().notNull(),
  power2: boolean().notNull(),

  createdAt: timestamp().defaultNow().notNull(),
  udpatedAt: timestamp({ mode: 'date', precision: 3 }).defaultNow().$onUpdate(() => new Date()).notNull()
})