package com.asgmt.matwam.store.local.weather;

import android.os.Parcel;
import android.os.Parcelable;

import androidx.room.Entity;
import androidx.room.Ignore;
import androidx.room.PrimaryKey;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.Objects;

@Entity
public class Weather implements Parcelable {

    @PrimaryKey(autoGenerate = true)
    public Long id;

    public String label;
    public String place;
    public String icon;
    public String summary;

    @Ignore
    public boolean isLoading;

    public Weather() {}


    public static Weather create(int id, String label, String place) {
        Weather weather = new Weather();
        weather.id = (long) id;
        weather.label = label;
        weather.place = place;
        return weather;
    }

    public static void update(String json, Weather weather) {
        try {
            JSONObject jo = new JSONObject(json);
            JSONObject joCurrent = jo.optJSONObject("current");
            JSONObject joCondition = joCurrent.optJSONObject("condition");
            weather.icon = String.format("http:%s", joCondition.optString("icon"));
            weather.summary = joCondition.optString("text");
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    protected Weather(Parcel in) {
        if (in.readByte() == 0) {
            id = null;
        } else {
            id = in.readLong();
        }
        label = in.readString();
        place = in.readString();
        icon = in.readString();
        summary = in.readString();
        isLoading = in.readByte() != 0;
    }

    public static final Creator<Weather> CREATOR = new Creator<Weather>() {
        @Override
        public Weather createFromParcel(Parcel in) {
            return new Weather(in);
        }

        @Override
        public Weather[] newArray(int size) {
            return new Weather[size];
        }
    };

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel parcel, int i) {
        if (id == null) {
            parcel.writeByte((byte) 0);
        } else {
            parcel.writeByte((byte) 1);
            parcel.writeLong(id);
        }
        parcel.writeString(label);
        parcel.writeString(place);
        parcel.writeString(icon);
        parcel.writeString(summary);
        parcel.writeByte((byte) (isLoading ? 1 : 0));
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Weather weather = (Weather) o;
        return isLoading == weather.isLoading &&
                Objects.equals(id, weather.id) &&
                Objects.equals(label, weather.label) &&
                Objects.equals(place, weather.place) &&
                Objects.equals(icon, weather.icon) &&
                Objects.equals(summary, weather.summary);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, label, place, icon, summary, isLoading);
    }

    @Override
    public String toString() {
        return "Weather{" +
                "id=" + id +
                ", label='" + label + '\'' +
                ", place='" + place + '\'' +
                ", icon='" + icon + '\'' +
                ", summary='" + summary + '\'' +
                ", isLoading=" + isLoading +
                '}';
    }
}
