<template>
  <v-dialog v-model="dialog" persistent max-width="800px">
    <v-card>
      <v-card-title>
        <span class="headline">Analiza ostatnich 25 pomiarów</span>
      </v-card-title>
      <v-card-text>
        <v-container>
          <v-row>
            <v-col cols="12" sm="6" md="6">
              <v-text-field
                label="Imię"
                v-model="cart.name"
                required
                disabled
              ></v-text-field>
            </v-col>
            <v-col cols="12" sm="6" md="6">
              <v-text-field
                label="Nazwisko"
                v-model="cart.id"
                disabled
              ></v-text-field>
            </v-col>
          </v-row>
        </v-container>
      </v-card-text>
      <v-card-actions>
        <v-spacer></v-spacer>
        <v-btn color="blue darken-1" text @click="dialog = false">
          Zamknij
        </v-btn>
      </v-card-actions>
    </v-card>
  </v-dialog>
</template>

<script>
import { mapState } from 'vuex';

export default {
  name: 'DialogComponent',
  props: {
    cartItem: [Object],
    value: [Boolean]
  },
  data() {
    return {
        item: {},
    }
  },
  methods: {
    close() {
      this.dialog = false;
    }
  },
  computed: {
    ...mapState({
      cart: (state) => state.cart.cartDetails,
    }),
    dialog: {
      get() {
        return this.value;
      },
      set(value) {
        this.$emit('input', value);
      }
    }
  },

};
</script>

<style scoped>

</style>
