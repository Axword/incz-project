<template>
  <v-app>
    <v-main>
      <NavbarComponent />
      <router-view class="mx-8 mb-8"></router-view>
    </v-main>
    <FooterComponent />
  </v-app>
</template>

<script>
import { mapState } from "vuex";

import NavbarComponent from "@/components/NavbarComponent";
import FooterComponent from "@/components/FooterComponent";
export default {
  name: "App",
  components: {
    NavbarComponent,
    FooterComponent,
  },

  computed: {
    ...mapState({
      snackbarOpened: (state) => state.snackbar.opened,
      snackbarMessage: (state) => state.snackbar.message,
      snackbarColor: (state) => state.snackbar.color,
    }),
    snackbar: {
      get() {
        return this.snackbarOpened;
      },
      set() {
        this.hideMessage();
      },
    },
    currentRouteName() {
      return this.$route.name;
    },
  },
};
</script>

<style>
.v-snack__content {
  white-space: pre-line;
}
h2 {
  font-size: 200%;
  font-weight: 450;
}
h1 {
  font-weight: 500;
}
</style>
