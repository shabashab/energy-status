import { desc } from "drizzle-orm"
import { db } from "../db"
import { updates } from "../db/schema"

export default defineEventHandler(async (event) => {
  const lastUpdate = await db.query.updates.findFirst({
    orderBy: desc(updates.createdAt)
  })

  const updatesCount = await db.$count(updates)

  return {
    lastUpdate: lastUpdate ?? null,
    updatesCount
  }
})