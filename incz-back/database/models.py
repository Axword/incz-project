from django.db import models

class Cart(models.Model):
    size = models.CharField(null=True, blank=True, max_length=128)
    name = models.CharField(null=True, blank=True, max_length=256)
    
    class Meta:
        db_table = "Cart"

class Measurement(models.Model):
    timestamp = models.DateTimeField(auto_now_add=True, verbose_name='timestamp')
    measure_y_one = models.FloatField(null=True, blank=True, default=0)
    measure_y_two = models.FloatField(null=True, blank=True ,default=0)
    measure_z_one = models.FloatField(null=True, blank=True, default=0)
    measure_z_two = models.FloatField(null=True, blank=True ,default=0)
    measure_reciver_one = models.FloatField(null=True, blank=True, default=0)
    measure_reciver_two = models.FloatField(null=True, blank=True ,default=0)
    cart_id = models.ForeignKey("database.Cart", on_delete=models.CASCADE, related_name='cart')

    class Meta:
        db_table = "Measurment"