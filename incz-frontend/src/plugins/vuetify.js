import Vue from 'vue';
import Vuetify from 'vuetify/lib/framework';
import '@mdi/font/css/materialdesignicons.css' // Ensure you are using css-loader
import pl from 'vuetify/lib/locale/pl'

Vue.use(Vuetify);

export default new Vuetify({
    lang: {
        locales: { pl},
        current: 'pl',
      },
    icons: {
        iconfont: 'mdi', // default - only for display purposes
      },
});
