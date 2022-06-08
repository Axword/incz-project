<template>
  <div class="cart">
    <v-main class="elevation-0 mt-10 px-5 py-5">
      <v-data-table
        :headers="headers"
        :items="items"
        :fetch-objects="fetchCartList"
        :hide-default-footer="true"
        locale="pl-PL"
        class="elevation-1"
      >
        <template v-slot:[`item.actions`]="{ item }">
          <v-btn icon title="Zobacz ostatnie wyniki" @click="editItem(item)">
            <v-icon> mdi-tag-search </v-icon>
          </v-btn>
          <v-btn icon title="Usuń koszyk" @click="deleteItem(item)">
            <v-icon> mdi-delete-forever </v-icon>
          </v-btn>
          <v-btn icon title="Zobacz analize wyników" @click="analizeItem(item)">
            <v-icon> mdi-poll </v-icon>
          </v-btn>
        </template>
      </v-data-table>
    </v-main>
    <DialogComponent
    v-model="dialog"
    :cartItem="cartItem"
    />
  </div>
</template>

<script>
// @ is an alias to /src
import DialogComponent from "@/components/DialogComponent.vue";
import { mapState, mapActions, mapMutations } from "vuex";
import router from "@/router";
export default {
  name: "CartTable",
  components: {DialogComponent},
  data() {
    return {
      options: {},
      dialog: false,
      cartItem: {},
    };
  },
  methods: {
    ...mapActions(["fetchCartList", "deleteCart", "fetchCart"]),
    ...mapMutations(["setCartId"]),
    async deleteItem(item) {
      (await confirm("Czy na pewno chcesz usunąć koszyk?")) &&
        this.deleteCart(item);
    },
    editItem(item) {
      router.push({ name: "basketView", params: { id: item.id } });
    },
    analizeItem(item) {
      this.fetchCart(item.id)
      this.dialog = true
    }
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
