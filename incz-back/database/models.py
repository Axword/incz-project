from django.db import models
from django.utils import timezone

class Cart(models.Model):
    size = models.CharField(null=True, blank=True, max_length=128)
    name = models.CharField(null=True, blank=True, max_length=256)
    
    class Meta:
        db_table = "Cart"

class Measurement(models.Model):
    timestamp = models.DateTimeField(verbose_name='timestamp', blank=True, null=True, default=timezone.now)
    measure_acceleration_total_vector = models.FloatField(null=True, blank=True, default=0)
    measure_angle_pitch = models.FloatField(null=True, blank=True ,default=0)
    measure_acceleration_pitch = models.FloatField(null=True, blank=True ,default=0)
    measure_angle_yaw = models.FloatField(null=True, blank=True, default=0)
    measure_acceleration_yaw = models.FloatField(null=True, blank=True ,default=0)
    measure_reciver_one_rx = models.FloatField(null=True, blank=True, default=0)
    measure_reciver_two_rx = models.FloatField(null=True, blank=True ,default=0)
    cart_id = models.ForeignKey("database.Cart", on_delete=models.CASCADE, related_name='cart')

    class Meta:
        db_table = "Measurment"