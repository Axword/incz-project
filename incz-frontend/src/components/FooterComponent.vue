<template>
  <v-footer app bottom fixed style="width: 100%" padless>
    <v-card elevation="0" rounded="0" width="100%" class="bg-grey text-center">
      <v-divider></v-divider>

      <v-card-text class="text-white">
        {{ new Date().getFullYear() }} —
        <strong>Aplikacja przygotowana na przedmiot INCZ</strong>
      </v-card-text>
    </v-card>
  </v-footer>
</template>
