<template min-height:500 lang="">
  <nav>
    <v-app-bar color="primary">
      <template v-slot:img="{ props }">
        <v-img
          v-bind="props"
          gradient="to top right, rgba(19,84,122,0.8), rgba(128,208,199,.8)"
        ></v-img>
      </template>
      <v-spacer></v-spacer>
      <v-app-bar-title class="text-uppercase">
        <span class="font-weight-light white--text"
          >Monitoring i analiza danych z mikrokontrolera</span
        >
      </v-app-bar-title>
      <v-spacer></v-spacer>
    </v-app-bar>
  </nav>
</template>
<script>
export default {
  data() {
    return {};
  },
};
</script>
