import Vue from 'vue'
import VueRouter from 'vue-router'
import CartTableView from "../views/CartTableView.vue";
import FormatView from "../views/CartMeasurmentView.vue";

Vue.use(VueRouter)

const routes = [
  {
    path: "/",
    name: "CartTable",
    component: CartTableView,
  },
  {
    path: "/basket/:id/measurment/",
    name: "basketView",
    component: FormatView,
  },
]

const router = new VueRouter({
  routes
})

export default router
