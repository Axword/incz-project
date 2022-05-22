import Vue from "vue";
import Vuex from "vuex";

import measurement from "./measurment";

import cart from "./cart";
import snackbar from "./snackbar";

Vue.use(Vuex);

const store = new Vuex.Store({
  state: {},
  mutations: {},
  actions: {},
  modules: {
    snackbar,
    cart,
    measurement,
  },
});

export default store;
