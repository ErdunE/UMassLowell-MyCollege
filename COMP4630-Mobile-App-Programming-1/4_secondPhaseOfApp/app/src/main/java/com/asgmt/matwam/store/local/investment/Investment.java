package com.asgmt.matwam.store.local.investment;

import android.os.Parcel;
import android.os.Parcelable;

import androidx.room.Entity;
import androidx.room.Ignore;
import androidx.room.PrimaryKey;

import com.asgmt.matwam.store.local.weather.Weather;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.Date;
import java.util.Objects;

@Entity
public class Investment implements Parcelable {

    @PrimaryKey(autoGenerate = true)
    public Long id;

    public String holder;
    public String name;
    public String symbol;
    public String open;
    public String high;
    public String low;
    public String close;

    @Ignore
    public boolean isLoading;

    public Investment() {}
    public static Investment create(String holder, String symbol, String name) {
        Investment investment = new Investment();
        investment.holder = holder;
        investment.symbol = symbol;
        investment.name = name;
        return investment;
    }
    public static void update(String json, Investment investment) {
        try {
            JSONObject jo = new JSONObject(json);
            JSONArray jaPrices = jo.optJSONArray("prices");
            if (jaPrices.length() > 0) {
                JSONObject joPrice = jaPrices.getJSONObject(0);
                investment.open = joPrice.optString("open");
                investment.high = joPrice.optString("high");
                investment.low = joPrice.optString("low");
                investment.close = joPrice.optString("close");
            }
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Investment that = (Investment) o;
        return isLoading == that.isLoading &&
                Objects.equals(id, that.id) &&
                Objects.equals(holder, that.holder) &&
                Objects.equals(name, that.name) &&
                Objects.equals(symbol, that.symbol) &&
                Objects.equals(open, that.open) &&
                Objects.equals(high, that.high) &&
                Objects.equals(low, that.low) &&
                Objects.equals(close, that.close);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, holder, name, symbol, open, high, low, close, isLoading);
    }

    protected Investment(Parcel in) {
        if (in.readByte() == 0) {
            id = null;
        } else {
            id = in.readLong();
        }
        holder = in.readString();
        name = in.readString();
        symbol = in.readString();
        open = in.readString();
        high = in.readString();
        low = in.readString();
        close = in.readString();
        isLoading = in.readByte() != 0;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        if (id == null) {
            dest.writeByte((byte) 0);
        } else {
            dest.writeByte((byte) 1);
            dest.writeLong(id);
        }
        dest.writeString(holder);
        dest.writeString(name);
        dest.writeString(symbol);
        dest.writeString(open);
        dest.writeString(high);
        dest.writeString(low);
        dest.writeString(close);
        dest.writeByte((byte) (isLoading ? 1 : 0));
    }

    @Override
    public int describeContents() {
        return 0;
    }

    public static final Creator<Investment> CREATOR = new Creator<Investment>() {
        @Override
        public Investment createFromParcel(Parcel in) {
            return new Investment(in);
        }

        @Override
        public Investment[] newArray(int size) {
            return new Investment[size];
        }
    };
}
