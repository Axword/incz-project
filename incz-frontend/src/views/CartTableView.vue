<template>
  <div class="cart">
    <v-main class="elevation-0 mt-10 px-5 py-5">
      <TestTable
        :headers="headers"
        :items="items"
        :items-count="count"
        :get-items-per-page="itemsPerPage"
        :set-items-per-page="setCartItemsPerPage"
        :fetch-objects="fetchCartList"
        locale="pl-PL"
        class="elevation-1"
      >
        <template v-slot:[`item.actions`]="{ item }">
          <v-btn icon title="Zobacz szczegóły koszyka" @click="editItem(item)">
            <v-icon> mdi-pencil </v-icon>
          </v-btn>
          <v-btn icon title="Usuń koszyk" @click="deleteItem(item)">
            <v-icon> mdi-account-cancel </v-icon>
          </v-btn>
        </template>
      </TestTable>
    </v-main>
  </div>
</template>

<script>
// @ is an alias to /src
import TestTable from "@/components/TestTable";
import { mapState, mapMutations, mapActions } from "vuex";
import router from "@/router";
export default {
  name: "CartTable",
  components: { TestTable },
  data() {
    return {
      options: {},
    };
  },
  methods: {
    ...mapMutations(["setCartItemsPerPage"]),
    ...mapActions(["fetchCartList", "deleteCart"]),
    async deleteItem(item) {
      (await confirm("Czy na pewno chcesz usunąć koszyk?")) &&
        this.deleteCart(item);
    },
    editItem(item) {
      router.push({ name: "basketView", params: { id: item.id } });
    },
  },
  computed: {
    ...mapState({
      errors: (state) => state.cart.errors,
      count: (state) => state.cart.totalCartsItems,
      headers: (state) => state.cart.cartListHeaders,
      items: (state) => state.cart.cartList,
      itemsPerPage: (state) => state.cart.cartsPerPage,
    }),
  },
  async created() {
    this.fetchCartList();
  },
};
</script>
