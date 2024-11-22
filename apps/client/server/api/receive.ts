import { db } from "../db"
import { updates } from "../db/schema"

export default defineEventHandler(async (event) => {
  const rawBody = await readRawBody(event).catch((err) => {
    console.log(err)
    return false
  })

  if (typeof rawBody !== 'string') {
    return {}
  }

  const bodyDataPairs = rawBody
    .split(';')
    .map((pair) => pair.trim())
    .map((pair) => pair.split(':') as [string, string])

  const temperature = parseFloat(bodyDataPairs.find(([key]) => key === 'temperature')![1])
  const humidity = parseFloat(bodyDataPairs.find(([key]) => key === 'humidity')![1])
  const power1 = bodyDataPairs.find(([key]) => key === 'power1')![1] === '1'
  const power2 = bodyDataPairs.find(([key]) => key === 'power2')![1] === '1'

  console.log({
    temperature,
    humidity,
    power1,
    power2
  })

  await db.insert(updates).values({
    humidity,
    temperature,
    power1,
    power2,
  })

  return {}
})