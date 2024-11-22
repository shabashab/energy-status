<script setup lang="ts">
import { useIntervalFn } from '@vueuse/core';

const { data, refresh } = await useFetch('/api/stats')

useIntervalFn(async () => {
  await refresh()
}, 1000);
</script>

<template>
  <div class="w-screen min-h-screen grid place-items-center px-4">
    <div class="flex flex-row justify-between w-full lg:w-[400px]">
      <div class="flex flex-col items-start gap-6">
        <div class="flex flex-col items-start">
          <div class="text-3xl font-bold">
            {{ data?.lastUpdate?.temperature }} ºC 
          </div>
          <div>
            Temperature
          </div>
        </div>
        <div class="flex flex-col items-start">
          <div class="text-3xl font-bold">
            {{ data?.lastUpdate?.humidity }}  %
          </div>
          <div>
            Humidity
          </div>
        </div>
      </div>
      <div class="flex flex-col items-end gap-6">
        <div class="flex flex-col items-end">
          <div class="text-3xl font-bold">
            {{ data?.lastUpdate?.power1 ? "ON" : "OFF" }}
          </div>
          <div>
            Power 1
          </div>
        </div>
        <div class="flex flex-col items-end">
          <div class="text-3xl font-bold">
            {{ data?.lastUpdate?.power2 ? "ON" : "OFF" }}
          </div>
          <div>
            Power 2
          </div>
        </div>
      </div>
    </div>
    <div class="absolute left-1/2 -translate-x-1/2 bottom-8 opacity-50">
      Last update: {{ data?.lastUpdate?.createdAt ? new Date(data?.lastUpdate?.createdAt).toLocaleString("uk") : "none" }}
    </div>
  </div>
</template>
