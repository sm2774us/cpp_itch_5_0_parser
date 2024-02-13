#ifndef ITCH_PARSER_C_H
#define ITCH_PARSER_C_H

/*!
 * @file  itch.h
 * @abstract Helix C bindings.
 */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

  /*!
   * @enum     itch_parser_error_t
   * @abstract Function result.
   */
  typedef enum
  {
    /*! An unknown message type was received. */
    ITCH_PARSER_ERROR_UNKNOWN_MESSAGE_TYPE = -1,
    /*! A truncated packet was received. */
    ITCH_PARSER_ERROR_TRUNCATED_PACKET = -2,
    /*! An unknown error occurred. */
    ITCH_PARSER_ERROR_UNKNOWN = -3,
  } itch_parser_result_t;

  /*!
   * @typedef itch_parser_timestamp_t
   * @abstract Type of a timestamp.
   */
  typedef uint64_t itch_parser_timestamp_t;

  /*!
   * @typedef itch_parser_price_t
   * @abstract Type of a price.
   */
  typedef uint64_t itch_parser_price_t;

  /*!
   * @typedef  itch_parser_protocol_t
   * @abstract Type of a protocol descriptor.
   */
  typedef struct itch_parser_opaque_protocol *itch_parser_protocol_t;

  /*!
   * @typedef  itch_parser_venue_t
   * @abstract Type of a venue.
   */
  typedef struct itch_parser_opaque_venue *itch_parser_venue_t;

  /*!
   * @typedef  itch_parser_symbol_t
   * @abstract Type of a symbol.
   */
  typedef struct itch_parser_opaque_symbol *itch_parser_symbol_t;

  /*!
   * @typedef  itch_parser_session_t
   * @abstract Type of a session.
   */
  typedef struct itch_parser_opaque_session *itch_parser_session_t;

  /*!
   * @typedef  itch_parser_subscription_t
   * @abstract Type of a subscription.
   */
  typedef struct itch_parser_opaque_subscription *itch_parser_subscription_t;

  /*!
   * @typedef  itch_parser_order_book_t
   * @abstract Type of an order book.
   */
  typedef struct itch_parser_opaque_order_book *itch_parser_order_book_t;

  /*!
   * @typedef  itch_parser_trade_t
   * @abstract Type of a trade.
   */
  typedef struct itch_parser_opaque_trade *itch_parser_trade_t;

  /*!
   * @typedef  itch_parser_event_t
   * @abstract Type of an event.
   */
  typedef struct itch_parser_opaque_event *itch_parser_event_t;

  /*!
   * @enum     itch_parser_event_mask_t
   * @abstract Event mask.
   */
  typedef enum
  {
    /*! Order book update. */
    HELIX_EVENT_ORDER_BOOK_UPDATE = 1UL << 0,
    /*! Trade. */
    HELIX_EVENT_TRADE = 1UL << 1,
    /*! Top of book price level sweep. */
    HELIX_EVENT_SWEEP = 1UL << 2,
  } itch_parser_event_mask_t;

  /*!
   * @abstract Returns a human-readable string for an error code.
   */
  const char *itch_parser_strerror(int error);

  /*!
   * @abstract Returns the event mask.
   */
  itch_parser_event_mask_t itch_parser_event_mask(itch_parser_event_t);

  /*!
   * @abstract Returns the event symbol.
   */
  const char *itch_parser_event_symbol(itch_parser_event_t);

  /*!
   * @abstract Returns the timestamp of an event.
   */
  itch_parser_timestamp_t itch_parser_event_timestamp(itch_parser_event_t);

  /*!
   * @abstract Returns an order book from an event.
   *
   * The function returns an order book object if HELIX_EVENT_ORDER_BOOK_UPDATE
   * bit is set in the event mask.
   */
  itch_parser_order_book_t itch_parser_event_order_book(itch_parser_event_t);

  /*!
   * @abstract Returns a trade from an event object.
   *
   * The function returns a trade object if HELIX_EVEN_TRADE bit is set in the
   * event mask.
   */
  itch_parser_trade_t itch_parser_event_trade(itch_parser_event_t);

  /*!
   * @typedef  itch_parser_event_callback_t
   * @abstract Type of an event callback.
   */
  typedef void (*itch_parser_event_callback_t)(itch_parser_session_t, itch_parser_event_t);

  /*!
   * @typedef  itch_parser_send_callback_t
   * @abstract Type of a send packet callback.
   */
  typedef void (*itch_parser_send_callback_t)(itch_parser_session_t, char *, size_t);

  /*!
   * @enum     itch_parser_trading_state_t
   * @abstract Order book instrument trading state.
   */
  typedef enum
  {
    /*! Order book instrument trading state is unknown. */
    HELIX_TRADING_STATE_UNKNOWN,
    /*! Order book instrument trading is halted. */
    HELIX_TRADING_STATE_HALTED,
    /*! Order book instrument trading is paused. */
    HELIX_TRADING_STATE_PAUSED,
    /*! Order book instrument is in quotation only period. */
    HELIX_TRADING_STATE_QUOTATION_ONLY,
    /*! Order book instrument is trading at the exchange. */
    HELIX_TRADING_STATE_TRADING,
    /*! Order book instrument is traded in intraday auction. */
    HELIX_TRADING_STATE_AUCTION,
  } itch_parser_trading_state_t;

  /*!
   * @enum     itch_parser_trade_sign_t
   * @abstract Trade sign.
   */
  typedef enum
  {
    /*! Trade was buyer-initiated. */
    HELIX_TRADE_SIGN_BUYER_INITIATED,
    /*! Trade was seller-initiated. */
    HELIX_TRADE_SIGN_SELLER_INITIATED,
    /*! Trade was crossing. */
    HELIX_TRADE_SIGN_CROSSING,
    /*! Trade was matched with a non-displayable order. */
    HELIX_TRADE_SIGN_NON_DISPLAYABLE,
  } itch_parser_trade_sign_t;

  /*!
   * @abstract Returns the order book trading state.
   * @param    ob  Order book.
   */
  itch_parser_trading_state_t itch_parser_order_book_state(itch_parser_order_book_t);

  /*!
   * @abstract Returns the order book timestamp.
   */
  uint64_t itch_parser_order_book_timestamp(itch_parser_order_book_t);

  /*!
   * @abstract Returns the number of order book bid price levels.
   */
  size_t itch_parser_order_book_bid_levels(itch_parser_order_book_t);

  /*!
   * @abstract Returns the number of order book ask price levels.
   */
  size_t itch_parser_order_book_ask_levels(itch_parser_order_book_t);

  /*!
   * @abstract Returns the number of orders in the book.
   */
  size_t itch_parser_order_book_order_count(itch_parser_order_book_t);

  /*!
   * @abstract Returns the order book bid price for a price level.
   */
  itch_parser_price_t itch_parser_order_book_bid_price(itch_parser_order_book_t, size_t);

  /*!
   * @abstract Returns the order book bid size for a price level.
   */
  uint64_t itch_parser_order_book_bid_size(itch_parser_order_book_t, size_t);

  /*!
   * @abstract Returns the order book ask price for a price level.
   */
  itch_parser_price_t itch_parser_order_book_ask_price(itch_parser_order_book_t, size_t);

  /*!
   * @abstract Returns the order book ask size for a price level.
   */
  uint64_t itch_parser_order_book_ask_size(itch_parser_order_book_t, size_t);

  /*!
   * @abstract Returns midprice for a price level in the order book.
   */
  itch_parser_price_t itch_parser_order_book_midprice(itch_parser_order_book_t, size_t);

  /*!
   * @abstract Returns the trade timestamp.
   */
  uint64_t itch_parser_trade_timestamp(itch_parser_trade_t);

  /*!
   * @abstract Returns the trade sign.
   */
  itch_parser_trade_sign_t itch_parser_trade_sign(itch_parser_trade_t);

  /*!
   * @abstract Returns the price of a trade.
   */
  itch_parser_price_t itch_parser_trade_price(itch_parser_trade_t);

  /*!
   * @abstract Returns the size of a trade.
   */
  uint64_t itch_parser_trade_size(itch_parser_trade_t);

  /*!
   * @abstract Lookup a market data protocol.
   */
  itch_parser_protocol_t itch_parser_protocol_lookup(const char *name);

  /*!
   * @abstract Destroy a protocol object.
   */
  void itch_parser_protocol_destroy(itch_parser_protocol_t proto);

  /*!
   * Create a new session.
   */
  itch_parser_session_t itch_parser_session_create(itch_parser_protocol_t, itch_parser_event_callback_t, void *data);

  /*!
   * Destroy a session object.
   */
  void itch_parser_session_destroy(itch_parser_session_t session);

  /*!
   * @abstract Sets the session send callback.
   */
  void itch_parser_session_set_send_callback(itch_parser_session_t, itch_parser_send_callback_t);

  /*!
   * @abstract Returns session opaque context data.
   */
  void *itch_parser_session_data(itch_parser_session_t);

  /*!
   * @abstract Returns true if timestamp is in the range of regular trading hours.
   */
  bool itch_parser_session_is_rth_timestamp(itch_parser_session_t, itch_parser_timestamp_t);

  /*!
   * @abstract Process a packet for a session.
   *
   * This function is called by the packet I/O code to process raw packet data.
   */
  int itch_parser_session_process_packet(itch_parser_session_t, const char *buf, size_t len);

  /*!
   * @abstract Subscribe to listening to market data updates for a symbol.
   */
  void itch_parser_session_subscribe(itch_parser_session_t, const char *symbol, size_t max_orders);

  /*!
   * @abstract Unsubscribe a subscription from session.
   */
  void itch_parser_session_unsubscribe(itch_parser_subscription_t);

#ifdef __cplusplus
}
#endif

#endif
